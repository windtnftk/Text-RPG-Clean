using System;
using System.Collections.Concurrent;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Protocol;
using Protocol_IO;

namespace ServerApp
{
    public class Server : IDisposable
    {
        private const int Port = 9000;
        private const int MaxClients = 2;

        private readonly Socket _listenSocket;
        private readonly ConcurrentDictionary<ClientSession, Thread> _sessionWorkers = new();
        private readonly ConcurrentQueue<PacketEvent> _inboundQueue = new();
        private volatile bool _running;
        private Thread _acceptThread;
        private Thread _logicThread;
        private int _clientCount = 0;
        private bool _disposed;

        public Server()
        {
            _listenSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }

        public static void Main(string[] args)
        {
            using var server = new Server();
            server.Start();

            Console.CancelKeyPress += (sender, eventArgs) =>
            {
                eventArgs.Cancel = true;
                server.Stop();
            };

            server.Run();
        }

        public void Start()
        {
            _listenSocket.Bind(new IPEndPoint(IPAddress.Any, Port));
            _listenSocket.Listen(int.MaxValue);
            _running = true;

            _acceptThread = new Thread(AcceptLoop) { IsBackground = true };
            _logicThread = new Thread(LogicLoop) { IsBackground = true };

            _acceptThread.Start();
            _logicThread.Start();

            Console.WriteLine($"서버 ON : {Port} (멀티 클라)");
        }

        public void Run()
        {
            while (_running)
            {
                Thread.Sleep(100);
            }

            Stop();
        }

        public void Stop()
        {
            if (!_running)
            {
                return;
            }

            _running = false;

            try
            {
                _listenSocket.Close();
            }
            catch
            {
            }

            try
            {
                _listenSocket.Dispose();
            }
            catch
            {
            }

            JoinThread(_acceptThread);
            JoinThread(_logicThread);

            foreach (var kvp in _sessionWorkers)
            {
                SafeCloseSession(kvp.Key);
            }

            foreach (var kvp in _sessionWorkers)
            {
                JoinThread(kvp.Value);
            }

            _sessionWorkers.Clear();
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
            {
                return;
            }

            if (disposing)
            {
                Stop();
            }

            _disposed = true;
        }

        private void AcceptLoop()
        {
            while (_running)
            {
                Socket clientSocket;
                try
                {
                    clientSocket = _listenSocket.Accept();
                }
                catch (ObjectDisposedException)
                {
                    break;
                }
                catch (SocketException)
                {
                    if (!_running)
                    {
                        break;
                    }
                    continue;
                }

                var endPoint = clientSocket.RemoteEndPoint as IPEndPoint;
                if (endPoint == null)
                {
                    clientSocket.Close();
                    continue;
                }

                var session = new ClientSession(clientSocket, endPoint);
                var worker = new Thread(() => ClientWorker(session)) { IsBackground = true };
                if (_sessionWorkers.TryAdd(session, worker))
                {
                    worker.Start();
                }
                else
                {
                    clientSocket.Close();
                }
            }
        }

        private void ClientWorker(ClientSession session)
        {
            Protocol.IP_Port ipPort = Protocol_IO.Protocol_IO.GetIpPort(session.EndPoint);
            bool handshakeDone = false;

            try
            {
                while (_running)
                {
                    if (!Protocol_IO.Protocol_IO.ReceivePacket(session.Socket, out PacketType ptype, out byte[] payload))
                    {
                        LogDisconnectOrError(ipPort);
                        break;
                    }

                    if (!handshakeDone)
                    {
                        if (!TryHandshake(ptype, payload, session, ipPort))
                        {
                            break;
                        }
                        handshakeDone = true;
                        continue;
                    }

                    _inboundQueue.Enqueue(new PacketEvent(session, ptype, payload));
                }
            }
            finally
            {
                if (handshakeDone)
                {
                    int newCount = Interlocked.Decrement(ref _clientCount);
                    if (newCount < 0) Interlocked.Exchange(ref _clientCount, 0);
                    Console.WriteLine($"접속 해제: {(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port} -> 현재 접속 수: {Math.Max(0, _clientCount)}");
                }

                _sessionWorkers.TryRemove(session, out _);
                SafeCloseSession(session);
            }
        }

        private bool TryHandshake(PacketType ptype, byte[] payload, ClientSession session, Protocol.IP_Port ipPort)
        {
            if (ptype != PacketType.Hello)
            {
                Protocol_IO.Protocol_IO.SendErrorPacket(session.Socket, "handshake required");
                return false;
            }

            string msg = Encoding.UTF8.GetString(payload ?? Array.Empty<byte>());
            if (msg != "Hello")
            {
                Protocol_IO.Protocol_IO.SendErrorPacket(session.Socket, "invalid hello payload");
                return false;
            }

            int cur = Interlocked.Increment(ref _clientCount) - 1;
            if (cur >= MaxClients)
            {
                Interlocked.Decrement(ref _clientCount);
                string fullMsg = "현재 인원이 가득찼습니다.";
                Protocol_IO.Protocol_IO.SendErrorPacket(session.Socket, fullMsg);
                Console.WriteLine($"거부된 연결({(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port}) - 서버가 가득 참 (현재: {cur})");
                return false;
            }


            string welcome = $"Welcome. 현재 접속 인원: {cur}";
            byte[] welcomeBytes = Encoding.UTF8.GetBytes(welcome);
            Protocol_IO.Protocol_IO.SendPacket(session.Socket, PacketType.Welcome, welcomeBytes, (uint)welcomeBytes.Length);

            Console.WriteLine($"핸드셰이크 완료: {(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port} -> 현재 접속 수: {cur}");
            return true;
        }

        private void LogicLoop()
        {
            while (_running)
            {
                while (_inboundQueue.TryDequeue(out PacketEvent packetEvent))
                {
                    HandlePacketEvent(packetEvent);
                }

                Thread.Sleep(10);
            }

            while (_inboundQueue.TryDequeue(out PacketEvent remaining))
            {
                HandlePacketEvent(remaining);
            }
        }

        private void HandlePacketEvent(PacketEvent packetEvent)
        {
            Protocol.IP_Port ipPort = Protocol_IO.Protocol_IO.GetIpPort(packetEvent.Session.EndPoint);

            switch (packetEvent.Type)
            {
                case PacketType.Word:
                    HandleWord(packetEvent.Session.Socket, ipPort, packetEvent.Payload);
                    break;
                case PacketType.Position:
                    if (!HandlePosition(packetEvent.Session.Socket, ipPort, packetEvent.Payload))
                    {
                        Protocol_IO.Protocol_IO.SendErrorPacket(packetEvent.Session.Socket, "bad position payload");
                    }
                    break;
                default:
                    Protocol_IO.Protocol_IO.SendErrorPacket(packetEvent.Session.Socket, "unknown type");
                    break;
            }
        }

        private static void HandleWord(Socket clientSock, Protocol.IP_Port ipPort, byte[] payload)
        {
            string text = Encoding.UTF8.GetString(payload ?? Array.Empty<byte>());
            Console.WriteLine($"받은 단어({(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port}): {text}");
            Protocol_IO.Protocol_IO.SendPacket(clientSock, PacketType.AckSucces, Array.Empty<byte>(), 0);
        }


        private static bool HandlePosition(Socket clientSock, Protocol.IP_Port ipPort, byte[] payload)
        {
            if (payload == null || payload.Length != ProtocolHelper.POSITION_PAYLOAD_SIZE)
            {
                return false;
            }

            if (!ProtocolHelper.UnpackPositionPayload(payload, out uint x, out uint y))
            {
                return false;
            }

            Console.WriteLine($"받은 좌표({(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port}): ({x},{y})");
            Protocol_IO.Protocol_IO.SendPacket(clientSock, PacketType.PositionSucces, Array.Empty<byte>(), 0);
            return true;
        }

        private static void LogDisconnectOrError(Protocol.IP_Port ipPort)
        {
            Console.WriteLine($"클라이언트 연결 종료: {(string.IsNullOrEmpty(ipPort.ip) ? "unknown" : ipPort.ip)}:{ipPort.port}");
        }

        private static void JoinThread(Thread thread)
        {
            if (thread == null)
            {
                return;
            }

            if (thread.IsAlive)
            {
                thread.Join(500);
            }
        }

        private static void SafeCloseSession(ClientSession session)
        {
            if (session?.Socket == null)
            {
                return;
            }

            try
            {
                session.Socket.Shutdown(SocketShutdown.Both);
            }
            catch
            {
            }

            try
            {
                session.Socket.Close();
            }
            catch
            {
            }

            try
            {
                session.Socket.Dispose();
            }
            catch
            {
            }
        }

        private readonly struct PacketEvent
        {
            public ClientSession Session { get; }
            public PacketType Type { get; }
            public byte[] Payload { get; }

            public PacketEvent(ClientSession session, PacketType type, byte[] payload)
            {
                Session = session;
                Type = type;
                Payload = payload;
            }
        }

    }
}

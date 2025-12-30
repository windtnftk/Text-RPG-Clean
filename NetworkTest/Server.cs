using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Protocol;
using Protocol_IO;

namespace ServerApp
{
    public class Server
    {
        private const int Port = 9000;
        private const int MaxClients = 2;
        private static int _clientCount = 0;

        public static void Main(string[] args)
        {
            var listener = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            listener.Bind(new IPEndPoint(IPAddress.Any, Port));
            listener.Listen(int.MaxValue);

            Console.WriteLine($"서버 ON : {Port} (멀티 클라)");

            while (true)
            {
                Socket clientSocket = listener.Accept();
                var endPoint = clientSocket.RemoteEndPoint as IPEndPoint;
                if (endPoint == null)
                {
                    clientSocket.Close();
                    continue;
                }

                var session = new ClientSession(clientSocket, endPoint);
                Task.Run(() => ClientWorker(session));
            }
        }

        private static void ClientWorker(ClientSession session)
        {
            Protocol.IP_Port ipPort = Protocol_IO.Protocol_IO.GetIpPort(session.EndPoint);
            bool handshakeDone = false;

            try
            {
                while (true)
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

                    switch (ptype)
                    {
                        case PacketType.Word:
                            HandleWord(session.Socket, ipPort, payload);
                            break;
                        case PacketType.Position:
                            if (!HandlePosition(session.Socket, ipPort, payload))
                            {
                                Protocol_IO.Protocol_IO.SendErrorPacket(session.Socket, "bad position payload");
                            }
                            break;
                        default:
                            Protocol_IO.Protocol_IO.SendErrorPacket(session.Socket, "unknown type");
                            break;
                    }
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

                session.Socket.Close();
            }
        }


        private static bool TryHandshake(PacketType ptype, byte[] payload, ClientSession session, Protocol.IP_Port ipPort)
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

    }
}

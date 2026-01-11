using System;
using System.Collections.Concurrent;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Protocol;
using Protocol_IO;

namespace NetworkClientApp
{
    public class NetworkClient : IDisposable
    {
        private readonly ConcurrentQueue<PacketEvent> _recvQueue = new();
        private readonly object _sendLock = new();

        private Socket _socket;
        private Thread _recvThread;
        private volatile bool _running;
        private volatile bool _connected;

        public bool IsConnected => _connected;

        public bool Connect(string host, int port)
        {
            Disconnect();

            try
            {
                _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                _socket.Connect(host, port);

                // Hello -> Welcome 핸드셰이크
                byte[] hello = Encoding.UTF8.GetBytes("Hello");
                if (!Protocol_IO.Protocol_IO.SendPacket(_socket, PacketType.C2S_Hello, hello, (uint)hello.Length))
                {
                    CleanupSocket();
                    return false;
                }

                if (!Protocol_IO.Protocol_IO.ReceivePacket(_socket, out PacketType rtype, out byte[] rpayload))
                {
                    CleanupSocket();
                    return false;
                }

                if (rtype != PacketType.S2C_Welcome)
                {
                    CleanupSocket();
                    return false;
                }

                _recvQueue.Enqueue(new PacketEvent(rtype, rpayload));

                _running = true;
                _connected = true;

                _recvThread = new Thread(ReceiveLoop)
                {
                    IsBackground = true,
                    Name = "NetworkClient-Recv"
                };
                _recvThread.Start();

                return true;
            }
            catch
            {
                CleanupSocket();
                return false;
            }
        }

        public void Disconnect()
        {
            _running = false;
            _connected = false;

            try
            {
                _socket?.Shutdown(SocketShutdown.Both);
            }
            catch
            {
                // ignore
            }

            CleanupSocket();

            if (_recvThread != null && _recvThread.IsAlive)
            {
                _recvThread.Join(500);
            }
        }

        public bool SendWord(string msg)
        {
            if (!_connected || _socket == null) return false;

            byte[] bytes = Encoding.UTF8.GetBytes(msg ?? string.Empty);
            lock (_sendLock)
            {
                return Protocol_IO.Protocol_IO.SendPacket(_socket, PacketType.C2S_ChatMessage, bytes, (uint)bytes.Length);
            }
        }

        public bool SendPosition(uint x, uint y)
        {
            if (!_connected || _socket == null) return false;

            byte[] payload = ProtocolHelper.PackPositionPayload(x, y);
            lock (_sendLock)
            {
                return Protocol_IO.Protocol_IO.SendPacket(_socket, PacketType.C2S_PlaceStoneRequest, payload, ProtocolHelper.POSITION_PAYLOAD_SIZE);
            }
        }

        public bool TryDequeue(out PacketEvent packet)
        {
            return _recvQueue.TryDequeue(out packet);
        }

        public void Dispose()
        {
            Disconnect();
        }

        private void ReceiveLoop()
        {
            while (_running)
            {
                try
                {
                    if (!Protocol_IO.Protocol_IO.ReceivePacket(_socket, out PacketType type, out byte[] payload))
                    {
                        break;
                    }

                    _recvQueue.Enqueue(new PacketEvent(type, payload));
                }
                catch (SocketException)
                {
                    break;
                }
                catch (ObjectDisposedException)
                {
                    break;
                }
                catch
                {
                    break;
                }
            }

            _connected = false;
            _running = false;
            CleanupSocket();
        }

        private void CleanupSocket()
        {
            try
            {
                _socket?.Close();
            }
            catch
            {
                // ignore
            }

            _socket = null;
        }
    }
}
using System.Net.Sockets;
using Protocol;
using Protocol_IO;

namespace NetworkSend
{
    public static class ClientSend
    {
        public static bool Hello(Socket socket)
        {
            byte[] payload = PacketSerializer.BuildHello();
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.C2S_Hello, payload, (uint)payload.Length);
        }

        public static bool Chat(Socket socket, string text)
        {
            byte[] payload = PacketSerializer.BuildChat(text);
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.C2S_ChatMessage, payload, (uint)payload.Length);
        }

        public static bool Place(Socket socket, uint x, uint y)
        {
            byte[] payload = PacketSerializer.BuildPlace(x, y);
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.C2S_PlaceStoneRequest, payload, (uint)payload.Length);
        }
    }
}

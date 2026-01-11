using System.Net.Sockets;
using Protocol;
using Protocol_IO;

namespace NetworkSend
{
    public static class ServerSend
    {
        public static bool Welcome(Socket socket, string text)
        {
            byte[] payload = PacketSerializer.BuildWelcome(text);
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.S2C_Welcome, payload, (uint)payload.Length);
        }

        public static bool ChatMessage(Socket socket)
        {
            byte[] payload = PacketSerializer.BuildEmpty();
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.S2C_ChatMessage, payload, (uint)payload.Length);
        }

        public static bool PlaceStoneAck(Socket socket)
        {
            byte[] payload = PacketSerializer.BuildEmpty();
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.S2C_PlaceStoneAck, payload, (uint)payload.Length);
        }

        public static bool Error(Socket socket, string text)
        {
            byte[] payload = PacketSerializer.BuildError(text);
            return Protocol_IO.Protocol_IO.SendPacket(socket, PacketType.Error, payload, (uint)payload.Length);
        }
    }
}

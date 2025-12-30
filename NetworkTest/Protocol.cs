using System;
using System.Buffers.Binary;
using System.Text;

namespace Protocol
{
    public struct PacketHeader
    {
        public uint type; // network order
        public uint len;  // network order
    }

    public struct IP_Port
    {
        public string ip;
        public int port;
    }

    public enum PacketType : uint
    {
        Word = 1,
        Position = 2,

        Error = 255,

        // Handshake
        Hello = 10,
        Welcome = 11,

        // Responses
        AckSucces = 100,
        PositionSucces = 200,
        PlaceFail = 201,
    }

    public static class ProtocolHelper
    {
        public const uint MAX_PAYLOAD = 1024u * 1024u; // 1MB

        public const uint POSITION_PAYLOAD_SIZE = 8u;

        // host order (x,y) -> payload 8 bytes (network order)
        public static byte[] PackPositionPayload(uint x, uint y)
        {
            var buffer = new byte[POSITION_PAYLOAD_SIZE];
            BinaryPrimitives.WriteUInt32BigEndian(buffer.AsSpan(0, 4), x);
            BinaryPrimitives.WriteUInt32BigEndian(buffer.AsSpan(4, 4), y);
            return buffer;
        }

        // payload 8 bytes (network order) -> host order (x,y)
        public static bool UnpackPositionPayload(ReadOnlySpan<byte> payload, out uint outX, out uint outY)
        {
            outX = 0;
            outY = 0;

            if (payload.Length != POSITION_PAYLOAD_SIZE)
            {
                return false;
            }

            outX = BinaryPrimitives.ReadUInt32BigEndian(payload.Slice(0, 4));
            outY = BinaryPrimitives.ReadUInt32BigEndian(payload.Slice(4, 4));
            return true;
        }

        // Word payload는 "그냥 바이트"라서 별도 구조체 없음
        public static string PayloadToString(ReadOnlySpan<byte> payload)
        {
            // payload는 널종료가 아니라 length 기반이므로 그대로 string 생성
            return Encoding.UTF8.GetString(payload);
        }
    }
}
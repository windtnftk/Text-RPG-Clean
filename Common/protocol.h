#pragma once
#include <cstdint>
#include <cstring>
#include <string>

#if defined(_WIN32)
#include <winsock2.h>   // htonl, ntohl
#else
#include <arpa/inet.h>  // htonl, ntohl
#endif

namespace Protocol
{
	// 패킷 헤더: type/len은 "네트워크 바이트 오더"로 송수신
	struct PacketHeader
	{
		uint32_t type; // network order
		uint32_t len;  // network order
	};
	struct IP_Port
	{
		std::string ip{};
		int port=0;
	};
	// 테스트 코드 기준 타입들 (서버/클라 동일해야 함)
	enum class PacketType : uint32_t
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
	};

	// 공통 제한(테스트 코드에서 쓰는 값이랑 맞춤)
	constexpr uint32_t MAX_PAYLOAD = 1024u * 1024u; // 1MB

	// Position payload는 항상 8바이트 고정
	constexpr uint32_t POSITION_PAYLOAD_SIZE = 8u;

	// host order (x,y) -> payload 8 bytes (network order)
	inline void PackPositionPayload(char out8[POSITION_PAYLOAD_SIZE], uint32_t x, uint32_t y)
	{
		const uint32_t nx = htonl(x);
		const uint32_t ny = htonl(y);
		std::memcpy(out8, &nx, 4);
		std::memcpy(out8 + 4, &ny, 4);
	}

	// payload 8 bytes (network order) -> host order (x,y)
	inline bool UnpackPositionPayload(const char* payload, uint32_t len, uint32_t& outX, uint32_t& outY)
	{
		if (!payload || len != POSITION_PAYLOAD_SIZE) return false;

		uint32_t nx = 0, ny = 0;
		std::memcpy(&nx, payload, 4);
		std::memcpy(&ny, payload + 4, 4);

		outX = ntohl(nx);
		outY = ntohl(ny);
		return true;
	}

	// Word payload는 "그냥 바이트"라서 별도 구조체 없음
	inline std::string PayloadToString(const std::string& payload)
	{
		// payload는 널종료가 아니라 length 기반이므로 그대로 string 생성
		return std::string(payload.data(), payload.size());
	}
}

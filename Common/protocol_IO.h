#pragma once
#include <cstdint>
#include <cstring>
#include <string>
#include <iostream>
#if defined(_WIN32)
#include <winsock2.h>   // htonl, ntohl
#else
#include <arpa/inet.h>  // htonl, ntohl
#endif

namespace Protocol_IO
{
	bool SendAll(SOCKET s, const char* data, int len) {
		int total = 0;
		while (total < len) {
			int sent = send(s, data + total, len - total, 0);
			if (sent == SOCKET_ERROR) return false;
			total += sent;
		}
		return true;
	}
	bool RecvExact(SOCKET s, char* out, int len) {
		int total = 0;
		while (total < len) {
			int received = recv(s, out + total, len - total, 0);
			if (received == 0) return false;   // 서버 종료
			if (received < 0) return false;    // 오류
			total += received;
			//std::cout << "받은 총 바이트: " << total << "\n";
		}
		return true;
	}
	// 페이로드를 바이트 배열로 받음
	bool SendPacket(SOCKET s, Protocol::PacketType type, const char* payload, uint32_t len)
	{
		Protocol::PacketHeader h{};
		h.type = htonl((uint32_t)type);
		h.len = htonl(len);

		// 안전장치: 말도 안 되는 크기 차단
		if (len > Protocol::MAX_PAYLOAD) {
			std::cerr << "RecvPacket: payload too large: " << len << "\n";
			return false;
		}

		// 1) 헤더 8바이트 전송
		if (!SendAll(s, reinterpret_cast<const char*>(&h), (int)sizeof(h))) {
			std::cerr << "SendPacket: 헤더 전송 실패\n";
			return false;
		}

		// 2) payload 전송 (len == 0이면 생략)
		if (len == 0) return true;

		if (payload == nullptr) {
			std::cerr << "SendPacket: len>0 but payload is null\n";
			return false;
		}

		if (!SendAll(s, payload, static_cast<int>(len))) {
			std::cerr << "SendPacket: payload 전송 실패\n";
			return false;
		}

		return true;

	}
	// 페이로드를 문자열로 받음
	bool RecvPacket(SOCKET s, Protocol::PacketType& outType, std::string& outPayload)
	{
		Protocol::PacketHeader h{};

		// 1) 헤더 8바이트 받기
		if (!RecvExact(s, reinterpret_cast<char*>(&h), (int)sizeof(h))) {
			std::cerr << "RecvPacket: 헤더 수신 실패\n";
			return false;
		}

		// 2) 네트워크 바이트 오더 -> 호스트 바이트 오더 변환
		uint32_t type = ntohl(h.type);
		uint32_t len = ntohl(h.len);

		outType = static_cast<Protocol::PacketType>(type);

		// 3) 안전장치: 말도 안 되는 크기 차단 (클라이언트 측 제한)
		if (len > Protocol::MAX_PAYLOAD) {
			std::cerr << "RecvPacket: payload too large: " << len << "\n";
			return false;
		}

		// 4) 페이로드 받기
		outPayload.clear();
		if (len > 0) {
			outPayload.resize(len);
			if (!RecvExact(s, &outPayload[0], (int)len)) {
				std::cerr << "RecvPacket: payload 수신 실패\n";
				return false;
			}
		}

		return true;
	}
	bool SendWordPacket(SOCKET sock, const std::string& text) // 단어 전송
	{
		return SendPacket(sock, Protocol::PacketType::Word, text.data(), (uint32_t)text.size());
	}

	bool SendPositionPacket(SOCKET sock, uint32_t x, uint32_t y) // x,y 좌표 전송
	{

		char payload[Protocol::POSITION_PAYLOAD_SIZE];
		Protocol::PackPositionPayload(payload, x, y);
		return SendPacket(sock, Protocol::PacketType::Position, payload, Protocol::POSITION_PAYLOAD_SIZE);
	}
	void SendErrorPacket(SOCKET s, const std::string& msg) // 오류 패킷 전송
	{
		// 오류 메시지 전송
		SendPacket(s, Protocol::PacketType::Error, msg.c_str(), (uint32_t)msg.size());
	}
	std::string GetIpString(const sockaddr_in& addr)
	{
		char ipbuf[INET_ADDRSTRLEN]{};
		InetNtopA(AF_INET, &addr.sin_addr, ipbuf, INET_ADDRSTRLEN);
		return ipbuf;
	}
	int GetPort(const sockaddr_in& addr)
	{
		return ntohs(addr.sin_port);
	}
	Protocol::IP_Port GetIpPort(const sockaddr_in& addr)
	{
		Protocol::IP_Port result;
		result.ip = GetIpString(addr);
		result.port = GetPort(addr);
		return result;
	}
}

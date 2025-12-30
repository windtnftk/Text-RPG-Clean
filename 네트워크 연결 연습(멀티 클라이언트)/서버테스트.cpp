#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <windows.h> // FormatMessage 사용을 위해 winsock2.h 다음에 포함
#include <string> // 추가: std::string 사용
#include <atomic> // 접속자 수 카운트
#include "protocol.h"
#include "protocol_IO.h"

#pragma comment(lib, "ws2_32.lib")

int const MAX_CLIENTS = 2; // 최대 접속자 수
// 접속자 수 전역 카운트 (스레드 안전)
static std::atomic<int> g_client_count{ 0 };

struct ClientSession {
	SOCKET sock = INVALID_SOCKET;
	sockaddr_in addr{};
};


// 문자열 처리: 단순 로그 후 ACK 응답 전송
void HandleWord(SOCKET clientSock, Protocol::IP_Port IP_Port, const std::string& payload)
{
	// payload는 길이만큼의 문자열 바이트 (널 종료 없음)
	std::string text(payload.data(), payload.size());
	std::cout << "받은 단어(" << (IP_Port.ip.empty() ? IP_Port.ip : "unknown") << ":" << IP_Port.port << "): " << text << "\n";

	// 응답: AckSucces (페이로드 없음)
	Protocol_IO::SendPacket(clientSock, Protocol::PacketType::AckSucces, nullptr, 0);
}

// 좌표 처리: 클라이언트는 8바이트(2x uint32_t, 네트워크 바이트 오더)로 보냄
bool HandlePosition(SOCKET clientSock, Protocol::IP_Port IP_Port, const std::string& payload)
{
	uint32_t x = 0, y = 0; // 호스트 바이트 오더
	if (!Protocol::UnpackPositionPayload(payload.data(), payload.size(), x, y))
	{
		return false;
	}

	// 간단 검증 예: 음수는 허용하지 않음
	if (x < 0 || y < 0)
	{
		std::cout << "잘못된 좌표값: (" << x << "," << y << ")\n";
		return false;
	}

	std::cout << "받은 좌표(" << (IP_Port.ip.empty() ? IP_Port.ip : "unknown") << ":" << IP_Port.port << "): (" << x << "," << y << ")\n";

	// 응답: PositionSucces (페이로드 없음)
	Protocol_IO::SendPacket(clientSock, Protocol::PacketType::PositionSucces, nullptr, 0);
	return true;
}
void LogDisconnectOrError(Protocol::IP_Port IP_Port)
{
	// WSAGetLastError()가 0이면 보통 상대가 정상 종료(정상적인 disconnect)한 경우입니다.
	int err = WSAGetLastError();
	if (err == 0)
	{
		std::cout << "클라이언트 연결 종료: " << (IP_Port.ip.empty() ? IP_Port.ip : "unknown")
			<< ":" << IP_Port.port << "\n";
		return;
	}

	// 에러 코드가 있으면 텍스트로 변환해 출력
	LPSTR msgBuf = nullptr;
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);

	DWORD len = FormatMessageA(flags, nullptr, (DWORD)err, lang, (LPSTR)&msgBuf, 0, nullptr);
	if (len && msgBuf)
	{
		// 출력 (개발/디버그용)
		std::cout << "소켓 오류(" << err << ") - " << (IP_Port.ip.empty() ? IP_Port.ip : "unknown")
			<< ":" << IP_Port.port << " -> " << msgBuf;
		LocalFree(msgBuf);
	}
	else
	{
		std::cout << "소켓 오류(" << err << ") - " << (IP_Port.ip.empty() ? IP_Port.ip : "unknown")
			<< ":" << IP_Port.port << " (메시지 변환 실패)\n";
	}
}

bool Tryhandshake(Protocol::PacketType ptype, std::string& payload, ClientSession& ClientSession)
{
	Protocol::IP_Port ip_port = Protocol_IO::GetIpPort(ClientSession.addr);

	// 첫 메시지가 Hello가 아니면 거부
	if (ptype != Protocol::PacketType::Hello)
	{
		Protocol_IO::SendErrorPacket(ClientSession.sock, "handshake required");
		return false;
	}

	// payload가 "Hello"인지 간단 검증
	std::string msg(payload.data(), payload.size());
	if (msg != "Hello")
	{
		Protocol_IO::SendErrorPacket(ClientSession.sock, "invalid hello payload");
		return false;
	}

	// 접속자 수 체크: 이미 가득 찼으면 거부
	int cur = g_client_count.fetch_add(1);
	if (cur >= MAX_CLIENTS)
	{
		g_client_count.fetch_sub(1); // 증가한 것 취소
		std::string fullMsg = "현재 인원이 가득찼습니다.";
		// 오류 타입으로 알리고 연결 종료
		Protocol_IO::SendErrorPacket(ClientSession.sock, fullMsg);
		std::cout << "거부된 연결(" << (ip_port.ip.empty() ? "unknown" : ip_port.ip) << ":" << ip_port.port
			<< ") - 서버가 가득 참 (현재: " << cur << ")\n";

		return false;
	}

	// 허용: 접속자 수 증가 후 Welcome 전송 (증가 후 값을 포함)
	std::string welcome = std::string("Welcome. 현재 접속 인원: ") + std::to_string(cur);
	Protocol_IO::SendPacket(ClientSession.sock, Protocol::PacketType::Welcome, welcome.c_str(), (uint32_t)welcome.size());

	std::cout << "핸드셰이크 완료: " << (ip_port.ip.empty() ? "unknown" : ip_port.ip) << ":" << ip_port.port
		<< " -> 현재 접속 수: " << cur << "\n";

	// 핸드셰이크 완료 — 다음 반복부터 일반 패킷 처리
	return true;
}
void PayloadSwitch(Protocol::PacketType ptype, ClientSession& ClientSession, Protocol::IP_Port& ip_port, std::string& payload)
{
	switch (ptype)
	{
	case Protocol::PacketType::Word:
		// payload를 문자열(바이너리 길이 기반)로 해석
		HandleWord(ClientSession.sock, ip_port, payload);
		break;

	case Protocol::PacketType::Position:
		// payload는 8바이트: two uint32_t (네트워크 바이트 오더)
		if (!HandlePosition(ClientSession.sock, ip_port, payload))
		{
			// HandlePosition이 false면 에러 응답 전송
			Protocol_IO::SendErrorPacket(ClientSession.sock, "bad position payload");
		}
		break;

	default:
		Protocol_IO::SendErrorPacket(ClientSession.sock, "unknown type");
		break;
	}
}
// 수정: ClientWorker 변경점 통합 (핸드셰이크와 접속자 수 제한)
void ClientWorker(ClientSession ClientSession)
{
	Protocol::IP_Port ip_port = Protocol_IO::GetIpPort(ClientSession.addr);
	bool handshake_done = false; // 핸드셰이크 완료 여부
	while (true)
	{
		// 1) 헤더 8바이트를 정확히 받는다
		Protocol::PacketHeader hdr;
		if (!Protocol_IO::RecvExact(ClientSession.sock, (char*)&hdr, sizeof(hdr)))
		{
			LogDisconnectOrError(ip_port);
			break;
		}

		// 2) 네트워크 바이트 오더 -> 호스트 바이트 오더 변환
		uint32_t type = ntohl(hdr.type);
		uint32_t len = ntohl(hdr.len);
		Protocol::PacketType ptype = static_cast<Protocol::PacketType>(type);
		// 3) 안전장치: 말도 안 되는 payload 길이는 차단
		if (len > Protocol::MAX_PAYLOAD)
		{
			Protocol_IO::SendErrorPacket(ClientSession.sock, "payload too large");
			break; // 보통은 끊어버림
		}

		// 4) payload를 len만큼 정확히 받는다
		std::string payload;
		payload.resize(len);

		if (len > 0 && !Protocol_IO::RecvExact(ClientSession.sock, &payload[0], (int)len))
		{
			LogDisconnectOrError(ip_port);
			break;
		}

		// --- 핸드셰이크 처리: 첫 번째 유효한 메시지는 Hello 여야 함 ---
		if (!handshake_done)
		{
			if (!Tryhandshake(ptype, payload, ClientSession)) {
				break; // 핸드셰이크 실패 - 연결 종료
			}
			handshake_done = true;
			continue; // 핸드셰이크 성공 - 다음 반복부터 일반 패킷 처리
		}

		// 5) type에 따라 payload 해석/처리 (핸드셰이크 이후)
		PayloadSwitch(ptype, ClientSession, ip_port, payload);
	}

	// 연결 종료 시 접속자 수 감소 (핸드셰이크가 완료되어 카운트에 포함된 경우만)
	if (handshake_done)
	{
		int newCount = g_client_count.fetch_sub(1) - 1;
		if (newCount < 0) g_client_count.store(0);
		std::cout << "접속 해제: " << (ip_port.ip.empty() ? "unknown" : ip_port.ip) << ":" << ip_port.port
			<< " -> 현재 접속 수: " << g_client_count.load() << "\n";
	}

	closesocket(ClientSession.sock);
}

int main() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		std::cerr << "WSAStartup 실패\n";
		return 1;
	}

	SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET) {
		std::cerr << "socket 실패\n";
		WSACleanup();
		return 1;
	}

	// 재실행할 때 포트 바로 재사용(실습 편의)
	BOOL opt = TRUE;
	setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));

	sockaddr_in addr{};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // 모든 인터페이스에서 받기

	if (bind(listenSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
		std::cerr << "bind 실패\n";
		closesocket(listenSock);
		WSACleanup();
		return 1;
	}

	if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "listen 실패\n";
		closesocket(listenSock);
		WSACleanup();
		return 1;
	}

	std::cout << "서버 ON : " << ntohs(addr.sin_port) << " (멀티 클라)\n";

	// ✅ 루트B 핵심: accept를 계속 받고, 클라마다 스레드 분리
	while (true) {
		sockaddr_in clientAddr{};
		int clientLen = sizeof(clientAddr);
		SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientLen);

		ClientSession s;
		s.sock = clientSock;
		s.addr = clientAddr;

		std::thread(ClientWorker, s).detach();  // 복사
	}

	closesocket(listenSock);
	WSACleanup();
	return 0;
}


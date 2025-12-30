#include <winsock2.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <ws2tcpip.h>  // InetPton
#include "protocol.h"
#include "protocol_IO.h"
#pragma comment(lib, "ws2_32.lib")

// Winsock 에러 문자열 변환 (FormatMessage 사용)
static std::string WSAErrorToString(int code)
{
	LPSTR msgBuf = nullptr;
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	HMODULE ws2 = GetModuleHandleA("ws2_32.dll");
	if (ws2) {
		// Winsock 전용 메시지 우선 조회
		flags |= FORMAT_MESSAGE_FROM_HMODULE;
	}
	DWORD lang = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
	DWORD len = FormatMessageA(flags, ws2, (DWORD)code, lang, (LPSTR)&msgBuf, 0, nullptr);

	std::string result;
	if (len && msgBuf) {
		// 끝의 CR/LF 제거
		while (len > 0 && (msgBuf[len - 1] == '\n' || msgBuf[len - 1] == '\r')) --len;
		result.assign(msgBuf, len);
		LocalFree(msgBuf);
	}
	else {
		result = std::string("Unknown error (code=") + std::to_string(code) + ")";
	}
	return result;
}

// Connect with timeout (blocking socket is restored on return).
// timeout_ms: milliseconds
// outErr: optional, returns a winsock error code when connect fails/timeout.
static bool ConnectWithTimeout(SOCKET s, const sockaddr_in* addr, int addrlen, int timeout_ms, int* outErr = nullptr)
{
	// Set non-blocking
	u_long mode = 1;
	if (ioctlsocket(s, FIONBIO, &mode) == SOCKET_ERROR) {
		if (outErr) *outErr = WSAGetLastError();
		return false;
	}

	int ret = connect(s, reinterpret_cast<const sockaddr*>(addr), addrlen);
	if (ret == 0) {
		// connected immediately
		mode = 0;
		ioctlsocket(s, FIONBIO, &mode); // restore blocking
		return true;
	}

	int last = WSAGetLastError();
	if (last != WSAEWOULDBLOCK && last != WSAEINPROGRESS) {
		// immediate failure
		if (outErr) *outErr = last;
		mode = 0;
		ioctlsocket(s, FIONBIO, &mode);
		return false;
	}

	// wait for writability
	fd_set wf;
	FD_ZERO(&wf);
	FD_SET(s, &wf);

	timeval tv;
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec = (timeout_ms % 1000) * 1000;

	int sel = select(0, nullptr, &wf, nullptr, &tv);
	if (sel == 0) {
		// timeout
		if (outErr) *outErr = WSAETIMEDOUT;
		mode = 0;
		ioctlsocket(s, FIONBIO, &mode);
		return false;
	}
	if (sel == SOCKET_ERROR) {
		if (outErr) *outErr = WSAGetLastError();
		mode = 0;
		ioctlsocket(s, FIONBIO, &mode);
		return false;
	}

	// check SO_ERROR
	int so_err = 0;
	int optlen = sizeof(so_err);
	if (getsockopt(s, SOL_SOCKET, SO_ERROR, (char*)&so_err, &optlen) == SOCKET_ERROR) {
		if (outErr) *outErr = WSAGetLastError();
		mode = 0;
		ioctlsocket(s, FIONBIO, &mode);
		return false;
	}

	mode = 0;
	ioctlsocket(s, FIONBIO, &mode); // restore blocking

	if (so_err != 0) {
		if (outErr) *outErr = so_err;
		return false;
	}

	return true;
}


int main(int argc, char* argv[]) {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		std::cerr << "WSAStartup 실패\n";
		return 1;
	}

	std::string ip = "222.239.88.107";
	int port = 9000;
	std::string name = "guest";

	if (argc >= 2) ip = argv[1];
	if (argc >= 3) port = std::stoi(argv[2]);
	if (argc >= 4) name = argv[3];

	SetConsoleTitleA(name.c_str()); // ★ 멀티클라 구분용

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) {
		std::cerr << "socket 실패\n";
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((u_short)port);
	if (InetPtonA(AF_INET, ip.c_str(), &serverAddr.sin_addr) != 1) {
		std::cerr << "IP 변환 실패\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	// connect with timeout (5s)
	int err = 0;
	if (!ConnectWithTimeout(sock, &serverAddr, sizeof(serverAddr), 10000, &err)) {
		std::cerr << "connect 실패: code=" << err << " msg=\"" << WSAErrorToString(err) << "\"\n";
		closesocket(sock);
		WSACleanup();
		return 1;
	}

	std::cout << "[" << name << "] 서버 연결됨! (" << ip << ":" << port << ")\n";

	bool handshake_done = false;

	while (true) {
		// 첫 루프 진입 시(한 번만) Hello 전송 및 Welcome 수신으로 핸드셰이크
		if (!handshake_done) {
			// Hello 전송 (Word 대신 전용 Hello 타입 사용)
			const char* helloMsg = "Hello";
			if (!Protocol_IO::SendPacket(sock, Protocol::PacketType::Hello, helloMsg, (uint32_t)strlen(helloMsg))) {
				std::cerr << "핸드셰이크: Hello 전송 실패\n";
				break;
			}

			Protocol::PacketType rtype;
			std::string rpayload;
			if (!Protocol_IO::RecvPacket(sock, rtype, rpayload)) {
				std::cerr << "핸드셰이크: Welcome 수신 실패\n";
				break;
			}

			if (rtype == Protocol::PacketType::Welcome) {
				std::string welcomeMsg(rpayload.data(), rpayload.size());
				std::cout << "[" << name << "] 서버 Welcome: " << welcomeMsg << "\n";
				handshake_done = true;
			}
			else {
				std::cerr << "핸드셰이크 실패: 서버가 Welcome을 보내지 않았습니다. 타입=" << static_cast<uint32_t>(rtype) << "\n";
				break;
			}

			// 핸드셰이크가 완료되면 다음 반복에서 사용자 명령 처리
			continue;
		}

		std::string line;
		std::cout << "명령: w <text> | p <x> <y>\n";
		std::getline(std::cin, line);
		if (line == "quit") break;

		if (line.rfind("w ", 0) == 0) {
			Protocol_IO::SendWordPacket(sock, line.substr(2));
		}
		else if (line.rfind("p ", 0) == 0) {
			uint32_t x, y;
			if (sscanf_s(line.c_str() + 2, "%d %d", &x, &y) != 2)
			{
				std::cout << "형식 오류: p <x> <y>\n";
				continue;
			}

			Protocol_IO::SendPositionPacket(sock, x, y);
		}

		else {
			std::cout << "명령: w <text> | p <x> <y>\n";
			continue;
		}

		Protocol::PacketType rtype;
		std::string rpayload;
		if (!Protocol_IO::RecvPacket(sock, rtype, rpayload)) break;

		switch (rtype) {
		case Protocol::PacketType::AckSucces:
			std::cout << "[서버 응답] 단어 수신 성공\n";
			break;

		case Protocol::PacketType::PositionSucces:
			std::cout << "[서버 응답] 위치 수신 성공\n";
			break;

		case Protocol::PacketType::PlaceFail:
		{
			// 서버가 실패 사유를 페이로드로 보낼 수 있으므로 메시지로 변환해 출력
			std::string msg(rpayload.data(), rpayload.size());
			std::cout << "[서버 응답] 위치 등록 실패: " << msg << "\n";
			break;
		}

		case Protocol::PacketType::Error:
		{
			// Error 타입은 에러 메시지를 페이로드로 받음
			std::string errMsg(rpayload.data(), rpayload.size());
			std::cout << "[서버 응답] 오류: " << errMsg << "\n";
			break;
		}

		default:
			std::cout << "[서버 응답] 알 수 없는 타입: " << static_cast<uint32_t>(rtype) << "\n";
			break;
		}
	}

	closesocket(sock);
	WSACleanup();
	return 0;
}
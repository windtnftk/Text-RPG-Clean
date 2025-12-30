#include <winsock2.h>
#include <iostream>
#include <string>
#include <windows.h>
#include <ws2tcpip.h>  // InetPton
#pragma comment(lib, "ws2_32.lib")

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
		std::cout << "받은 총 바이트: " << total << "\n";
    }
    return true;
}

int main(int argc, char* argv[]) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup 실패\n";
        return 1;
    }

    std::string ip = "127.0.0.1";
    int port = 5000;
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

    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "connect 실패\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "[" << name << "] 서버 연결됨! (" << ip << ":" << port << ")\n";

    // 예: 'A' 10000개
    //std::string big(12345, 'A');
    //const int N = (int)big.size();

    while (true) {
        std::cout << "> enter 입력 시 12345바이트 전송 (quit 종료)\n";
        std::string cmd;
        if (!std::getline(std::cin, cmd)) break;
        if (cmd == "quit") break;

        // 🔹 1) 전부 전송
        if (!SendAll(sock, cmd.data(), cmd.size())) {
            std::cerr << "SendAll 실패\n";
            break;
        }

        // 🔹 2) 수신 버퍼 준비 (비어있는 string → 크기 확보)
        std::string echo;
        echo.resize(cmd.size());

        // 🔹 3) 전부 수신
        if (!RecvExact(sock, &echo[0], cmd.size())) {
            std::cerr << "RecvExact 실패\n";
            break;
        }

        // 너무 길어서 일부만 출력
        std::cout << "에코 수신 완료 (총 " << echo.size() << " bytes)\n";
        std::cout << "앞 30자: " << echo.substr(0, 30) << "\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}


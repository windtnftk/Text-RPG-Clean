#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

static bool SendAll(SOCKET s, const char* data, int len) {
    int total = 0;
    while (total < len) {
        int sent = send(s, data + total, len - total, 0);
        if (sent == SOCKET_ERROR) return false;
        total += sent;
    }
    return true;
}

static void ClientWorker(SOCKET clientSock, sockaddr_in clientAddr) {
    char ipStr[INET_ADDRSTRLEN]{};
    inet_ntop(AF_INET, &clientAddr.sin_addr, ipStr, sizeof(ipStr));
    int clientPort = ntohs(clientAddr.sin_port);

    std::cout << "[클라 접속] " << ipStr << ":" << clientPort << "\n";

    char buf[1024];
    while (true) {
        int received = recv(clientSock, buf, (int)sizeof(buf), 0);
        if (received == 0) {
            std::cout << "[클라 종료] " << ipStr << ":" << clientPort << "\n";
            break;
        }
        if (received < 0) {
            std::cout << "[recv 오류] " << ipStr << ":" << clientPort << "\n";
            break;
        }

        // 받은 만큼 그대로 에코 (중요: send도 부분전송 가능하니 SendAll)
        if (!SendAll(clientSock, buf, received)) {
            std::cout << "[send 오류] " << ipStr << ":" << clientPort << "\n";
            break;
        }
    }

    closesocket(clientSock);
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

    std::cout << "서버 ON : 0.0.0.0:5000 (멀티 클라)\n";

    // ✅ 루트B 핵심: accept를 계속 받고, 클라마다 스레드 분리
    while (true) {
        sockaddr_in clientAddr{};
        int clientLen = sizeof(clientAddr);

        SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientLen);
        if (clientSock == INVALID_SOCKET) {
            std::cerr << "accept 실패\n";
            break;
        }

        // 클라 담당 스레드 시작 (detach: 독립 실행)
        std::thread(ClientWorker, clientSock, clientAddr).detach();
    }

    closesocket(listenSock);
    WSACleanup();
    return 0;
}

// echo_server.cpp  (Windows / WinSock)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

int main() {
    // 1) WinSock 초기화
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup 실패\n";
        return 1;
    }

    // 2) 서버 소켓 생성 (TCP)
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "socket 실패\n";
        WSACleanup();
        return 1;
    }

    // 3) 주소/포트 바인드 (127.0.0.1:5000)
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(listenSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "bind 실패\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    // 4) 연결 대기 시작
    if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "listen 실패\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "서버 ON: 127.0.0.1:5000 (클라 접속 대기중)\n";

    // 5) 클라이언트 접속 수락
    sockaddr_in clientAddr{};
    int clientLen = sizeof(clientAddr);
    SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientLen);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "accept 실패\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "클라 접속됨!\n";

    // 6) Echo: recv -> send 반복
    char buf[1024];
    while (true) {
        int received = recv(clientSock, buf, sizeof(buf) - 1, 0);
        if (received <= 0) {
            std::cout << "클라 연결 종료/오류\n";
            break;
        }
        buf[received] = '\0';
        std::cout << "받음: " << buf << "\n";

        int sent = send(clientSock, buf, received, 0);
        if (sent == SOCKET_ERROR) {
            std::cout << "send 오류\n";
            break;
        }
    }

    // 7) 정리
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}

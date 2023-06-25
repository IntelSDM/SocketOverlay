#include "pch.h"
#include "Sockets.h"
#pragma comment(lib, "ws2_32.lib")
void main()
{
    WSADATA data;
    WORD ver = MAKEWORD(2, 2);
    int wsResult = WSAStartup(ver, &data);
    if (wsResult != 0)
    {
        std::cout << "Can't Connect1\n";
        return;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        std::cout << "Can't Connect2\n";
        WSACleanup();
        return;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(51000);
    inet_pton(AF_INET, "127.0.0.1", &hint.sin_addr);

    if (connect(sock, reinterpret_cast<sockaddr*>(&hint), sizeof(hint)) == SOCKET_ERROR)
    {
        std::cout << "Can't Connect3\n";
        closesocket(sock);
        WSACleanup();
        return;
    }

    std::cout << "Connected\n";

    while (true)
    {
        // Perform any necessary operations with the connected socket.
    }

    closesocket(sock);
    WSACleanup();

}
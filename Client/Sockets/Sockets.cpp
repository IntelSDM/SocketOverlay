#include "pch.h"
#include "Sockets.h"
#pragma comment(lib, "ws2_32.lib")

std::string IPAddress = "127.0.0.0";
int port = 51000;
SOCKET GlobalSocket;

void CreateSocket()
{
	WSAData data;
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
	}
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, IPAddress.c_str(), &hint.sin_addr);
	if (connect(sock, (sockaddr*)&hint, sizeof(hint)) == SOCKET_ERROR)
	{
		std::cout << "Can't Connect3\n";
		return;
	}
	std::cout << "Connected\n";
	GlobalSocket = sock;
}
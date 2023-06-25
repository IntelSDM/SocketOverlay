#include "pch.h"
#include "Sockets.h"
#pragma comment(lib, "ws2_32.lib")

void main()
{

	CreateSockets();
	std::thread listernerthread(AcceptClients);
	listernerthread.join();
}
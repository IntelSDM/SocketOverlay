#include "pch.h"
#include "Client.h"
sockaddr_in HInt;
SOCKET Listening;
#pragma comment(lib, "ws2_32.lib")
sockaddr_in ClientAddress;
void CreateSockets()
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	WSAStartup(ver, &wsData); // start the server
	Listening = socket(AF_INET, SOCK_STREAM, 0); // create socket instance

	HInt.sin_family = AF_INET; // declare the ip and port and connection rules
	HInt.sin_port = htons(54000);
	HInt.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(Listening, (sockaddr*)&HInt, sizeof(HInt)); // bind the connection rules to the listening socket
	listen(Listening, SOMAXCONN); // keep socket open

}
std::list<Client*> ClientList;
void AcceptClients()
{
	int clientSize = sizeof(ClientAddress);
	SOCKET socket;
	if ((socket = accept(Listening, (SOCKADDR*)&ClientAddress, &clientSize)) != INVALID_SOCKET)
	{
		Client* client = new Client(socket);
		ClientList.push_back(client);
	}
}
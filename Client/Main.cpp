#include "pch.h"
#pragma comment(lib, "ws2_32.lib")
#include "Config.h"
#include "Rectangle.h"
#include "Client.h"
#include <random>
Config ConfigInstance;
#pragma comment(lib, "ws2_32.lib")

sockaddr_in HInt;
SOCKET Listening;
sockaddr_in ClientAddress;
Client* TCPClient;
void CreateServer()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    WSAStartup(ver, &wsData); // start the server

    Listening = socket(AF_INET, SOCK_STREAM, 0); // create socket instance

    HInt.sin_family = AF_INET; // declare the ip and port and connection rules
    HInt.sin_port = htons(51000);
    HInt.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(Listening, reinterpret_cast<sockaddr*>(&HInt), sizeof(HInt)); // bind the connection rules to the listening socket
    listen(Listening, SOMAXCONN); // keep socket open
}

void AcceptClients()
{
    std::cout << "connection start\n";
    while (true)
    {

        int clientSize = sizeof(ClientAddress);
        SOCKET clientSocket = accept(Listening, reinterpret_cast<SOCKADDR*>(&ClientAddress), &clientSize);
        if (clientSocket != INVALID_SOCKET)
        {
            std::cout << "connection\n";
            Client client;
            client.Socket = clientSocket;
            TCPClient = &client;
           
        }
      
    }
}
void SendRectangles()
{
   
}
void main()
{	
	json j;
	ConfigInstance.ToJson(j);
	std::cout << j.dump() << "\n";

	CreateServer();
	std::thread listernerthread(AcceptClients);
  //  std::thread drawthread(SendRectangles);
//	drawthread.detach();
    listernerthread.detach();
    while (true)
    {
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, 1000);
        int randx = distribution(generator);
        int randy = distribution(generator);
        if (TCPClient)
        {
            RectangleJson rectjson1(randx, randy, 10, 10);
            json js;
            rectjson1.ToJson(js);
            TCPClient->SendText(js.dump());

        }
    }
}
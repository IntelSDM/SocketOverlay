#pragma once
#include "RectangleJson.h"
using ByteArray = std::vector<uint8_t>;
class Client
{

public:
	SOCKET Socket;
	std::string IpAddress;
	bool SendingBytes = false;
	void DrawingHandler();
	void MessageHandler();
	void SendText(std::string Text);
	std::string ReceiveText();

	std::list<json> RectangleList;
private:
	std::mutex RectangleListMutex;
};
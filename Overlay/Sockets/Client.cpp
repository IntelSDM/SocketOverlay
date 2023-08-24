#include "pch.h"
#include "Client.h"
#include "Graphics.h"
#include "Drawing.h"
constexpr int BufferSize = 4096;
void Client::SendText(std::string text)
{
	ByteArray plaintext(text.begin(), text.end());
	int32_t Result = send(Client::Socket, (char*)plaintext.data(), (int)plaintext.size(), 0);
}
void Client::MessageHandler()
{
	while (true)
	{
		std::string message = Client::ReceiveText(); // halts everything here, goes to recieve a message
		if (message.size() == 0)
			return;

		json jsoned = json::parse(message);
		if (jsoned[0]["Type"] == "Rectangle")
		{
			std::lock_guard<std::mutex> lock(RectangleListMutex);
			RectangleList = jsoned;
		}
	
	}
}
void Client::DrawingHandler()
{
	{ // locked region
		std::lock_guard<std::mutex> lock(RectangleListMutex);
		for (json jsonobject : RectangleList)
		{
			if (jsonobject["Type"] != "Rectangle")
				continue;

			RectangleJson rectjson;
			rectjson.FromJson(jsonobject);

			SwapChain->FillRectangle(rectjson.X, rectjson.Y, rectjson.W, rectjson.H, Colors::Red);
		}

	}

	
}
std::string Client::ReceiveText()
{
	ByteArray	ReceivedBytes;
	uint8_t		RecvBuffer[BufferSize];

	while (true)
	{
		int32_t Received = recv(Client::Socket, (char*)RecvBuffer, BufferSize, 0);

		if (Received < 0)
			break;

		for (int n = 0; n < Received; ++n)
		{
			ReceivedBytes.push_back(RecvBuffer[n]);
		}
		auto breaker = std::find(ReceivedBytes.begin(), ReceivedBytes.end(), '|');

		if (breaker != ReceivedBytes.end())
		{
			// Found the delimiter, construct the string up to the delimiter
			std::string str(ReceivedBytes.begin(), breaker);
			return str;
		}
		if (Received <= BufferSize)
			break;

	}
	std::string str(ReceivedBytes.begin(), ReceivedBytes.end());
	return str;
}
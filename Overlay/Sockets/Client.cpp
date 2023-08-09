#include "pch.h"
#include "Client.h"

constexpr int BufferSize = 4096;
void Client::SendText(std::string Text)
{
	std::string Send = Text;
	ByteArray plaintext(Send.begin(), Send.end());
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
		std::string type = jsoned["Type"];
		if (type == "Rectangle")
		{
			RectangleJson rectangle(0.0f,0.0f,0.0f,0.0f);
			rectangle.FromJson(type);
			RectangleList.push_back(rectangle);
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

		if (Received <= BufferSize)
			break;

	}
	std::string str(ReceivedBytes.begin(), ReceivedBytes.end());
	return str;
}
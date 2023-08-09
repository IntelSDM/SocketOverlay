#include "pch.h"
#include "Client.h"
#include "Graphics.h"
#include "Drawing.h"
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
		//	RectangleJson rectangle(0.0f, 0.0f, 0.0f, 0.0f);
		//	rectangle.FromJson(type);
		//	RectangleList.push_back(rectangle);
			test = message;
		}
	}
}
void Client::DrawingHandler()
{
	for (RectangleJson jsonobject : Client::RectangleList)
	{
		int x = jsonobject.X;
		int y = jsonobject.Y;
		int width = jsonobject.W;
		int height = jsonobject.H;

		SwapChain->FillRectangle(x, y, width, height, Colors::Red);
	}

	std::wstring widetext(test.begin(), test.end());
	Platform::String^ text = ref new Platform::String(widetext.c_str());
	SwapChain->DrawText(text, 100, 100, Colors::Red);
	
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
#pragma once
using ByteArray = std::vector<uint8_t>;
class Client
{

public:
	SOCKET Socket;
	std::string IpAddress;

	void SendText(std::string Text);
	std::string ReceiveText();
private:


};
#pragma once

#include <string>
#include <array>
#include <asio.hpp>

#include "NetProtocol.h"
#include "Buffer.h"

constexpr int DEFAULT_BUFLEN = 512;

class NetClient
{
public:
	bool Init();
	bool SetAddr(std::string address, std::string port);
	bool Connect();
	void Disconnect();
	void Process();

	bool IsConnected() { return Connected; };
private:
	void ProcessInput();
	void ProcessOutput();

	bool Connected = false;

	asio::io_context ioContext;
	asio::ip::tcp::resolver::results_type* EndPoint;

	u32 BytesReceive = 0;
	u32 BytesRealReceive = 0;

	Buffer SendBuff;
	Buffer RecvBuff;
};
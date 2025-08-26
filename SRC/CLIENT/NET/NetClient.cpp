#include <SDL3/SDL.h>

#include "Common.h"
#include "NetClient.h"

using asio::ip::tcp;

bool NetClient::Init()
{
	
	return true;
}

bool NetClient::SetAddr(std::string address, std::string port)
{
	tcp::resolver resolver(ioContext);
	EndPoint = &resolver.resolve(address, port);

	return true;
}

bool NetClient::Connect()
{
	Connected = true;

	return true;
}

void NetClient::Disconnect()
{
	Connected = false;

	SDL_Log("NET: Disconnected successful.\n");
}

void NetClient::Process()
{

}

void NetClient::ProcessInput()
{

}

void NetClient::ProcessOutput()
{

}
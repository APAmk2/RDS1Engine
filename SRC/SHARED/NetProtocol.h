#pragma once

enum NetMessageTypes : u8
{
	NET_PING = 0,
	
	NET_MAX
};

class NetMessage
{
public:
	NetMessageTypes MessageType = NET_MAX;
	std::vector<u8>* MessageData;
};
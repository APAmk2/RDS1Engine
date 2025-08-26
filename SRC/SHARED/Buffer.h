#pragma once

#include <vector>

#include "Common.h"

constexpr u32 DEF_NET_BUFF_SIZE = 2048;

class Buffer
{
public:
	Buffer();
	Buffer(u32 len);
	~Buffer();

	Buffer& operator<<(u32 i);
	Buffer& operator>>(u32& i);
	Buffer& operator<<(u16 i);
	Buffer& operator>>(u16& i);
	Buffer& operator<<(u8 i);
	Buffer& operator>>(u8& i);

	Buffer& operator<<(i32 i);
	Buffer& operator>>(i32& i);
	Buffer& operator<<(i16 i);
	Buffer& operator>>(i16& i);
	Buffer& operator<<(i8 i);
	Buffer& operator>>(i8& i);

	Buffer& operator<<(bool i);
	Buffer& operator>>(bool& i);

	void Push(char* from, u32 len);
	void DiscardOldData();

private:
	void GrowBuf(u32 grow);

	std::vector<u8>* DataBuf;
	u32 DataBufLen = 0;
	u32 CursorPos = 0;
	u32 BufEndPos = 0;
	bool IsError = false;
};
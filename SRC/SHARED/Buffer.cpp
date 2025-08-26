#include "Buffer.h"

Buffer::Buffer()
{
	DataBufLen = DEF_NET_BUFF_SIZE;
	DataBuf = new std::vector<u8>(DataBufLen);
}

Buffer::Buffer(u32 len)
{
	DataBufLen = len;
	DataBuf = new std::vector<u8>(DataBufLen);
}

Buffer::~Buffer()
{
	delete DataBuf;
}

Buffer& Buffer::operator<<(u32 i)
{
    if (IsError) return *this;
    if (BufEndPos + 4 >= DataBufLen)    
        GrowBuf(4);
    *(u32*)&DataBuf[BufEndPos] = i;
    BufEndPos += 4;
    return *this;
}

Buffer& Buffer::operator>>(u32& i)
{
    if (IsError) return *this;
    if (CursorPos + 4 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(u32*)&DataBuf[CursorPos];
    CursorPos += 4;
    return *this;
}

Buffer& Buffer::operator<<(u16 i)
{
    if (IsError) return *this;
    if (BufEndPos + 2 >= DataBufLen)
        GrowBuf(2);
    *(u16*)&DataBuf[BufEndPos] = i;
    BufEndPos += 2;
    return *this;
}

Buffer& Buffer::operator>>(u16& i)
{
    if (IsError) return *this;
    if (CursorPos + 2 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(u16*)&DataBuf[CursorPos];
    CursorPos += 2;
    return *this;
}

Buffer& Buffer::operator<<(u8 i)
{
    if (IsError) return *this;
    if (BufEndPos + 1 >= DataBufLen)
        GrowBuf(1);
    *(u8*)&DataBuf[BufEndPos] = i;
    BufEndPos += 1;
    return *this;
}

Buffer& Buffer::operator>>(u8& i)
{
    if (IsError) return *this;
    if (CursorPos + 1 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(u8*)&DataBuf[CursorPos];
    CursorPos += 1;
    return *this;
}

Buffer& Buffer::operator<<(i32 i)
{
    if (IsError) return *this;
    if (BufEndPos + 4 >= DataBufLen)
        GrowBuf(4);
    *(i32*)&DataBuf[BufEndPos] = i;
    BufEndPos += 4;
    return *this;
}

Buffer& Buffer::operator>>(i32& i)
{
    if (IsError) return *this;
    if (CursorPos + 4 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(i32*)&DataBuf[CursorPos];
    CursorPos += 4;
    return *this;
}

Buffer& Buffer::operator<<(i16 i)
{
    if (IsError) return *this;
    if (BufEndPos + 2 >= DataBufLen)
        GrowBuf(2);
    *(i16*)&DataBuf[BufEndPos] = i;
    BufEndPos += 2;
    return *this;
}

Buffer& Buffer::operator>>(i16& i)
{
    if (IsError) return *this;
    if (CursorPos + 2 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(i16*)&DataBuf[CursorPos];
    CursorPos += 2;
    return *this;
}

Buffer& Buffer::operator<<(i8 i)
{
    if (IsError) return *this;
    if (BufEndPos + 1 >= DataBufLen)
        GrowBuf(1);
    *(i8*)&DataBuf[BufEndPos] = i;
    BufEndPos += 1;
    return *this;
}

Buffer& Buffer::operator>>(i8& i)
{
    if (IsError) return *this;
    if (CursorPos + 1 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(i8*)&DataBuf[CursorPos];
    CursorPos += 1;
    return *this;
}

Buffer& Buffer::operator<<(bool i)
{
    if (IsError) return *this;
    if (BufEndPos + 1 >= DataBufLen)
        GrowBuf(1);
    *(i8*)&DataBuf[BufEndPos] = i;
    BufEndPos += 1;
    return *this;
}

Buffer& Buffer::operator>>(bool& i)
{
    if (IsError) return *this;
    if (CursorPos + 1 > DataBufLen)
    {
        IsError = true;
        return *this;
    }
    i = *(bool*)&DataBuf[CursorPos];
    CursorPos += 1;
    return *this;
}

void Buffer::Push(char* from, u32 len)
{
    if (!from || !len) return;
    if (BufEndPos + len >= DataBufLen)
        GrowBuf(len - DataBufLen);
    for (u32 i = 0; i < len; i++)
    {
        DataBuf->at(BufEndPos) = *(u8*)(from + i);
        BufEndPos++;
    }
}

void Buffer::DiscardOldData()
{
    if (IsError) return;
    if (CursorPos > BufEndPos)
    {
        IsError = true;
        return;
    }
    if (CursorPos)
    {
        for (u32 i = CursorPos; i < BufEndPos; i++)
            DataBuf[i - CursorPos] = DataBuf[i];
        BufEndPos -= CursorPos;
        CursorPos = 0;
    }
}

void Buffer::GrowBuf(u32 grow)
{
    DataBuf->resize(DataBufLen + grow);
    DataBufLen = DataBuf->size();
}
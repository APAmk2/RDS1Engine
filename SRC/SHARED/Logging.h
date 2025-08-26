#pragma once

#include <string>
#include <fstream>

#include "Types.h"

enum LogType : u8
{
	LOG_INFO = 0,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRIT_ERROR,
	
	LOG_MAX
};

class Logger
{
public:
	Logger(std::string name);
	~Logger();

	bool IsGood();

	void WriteLog(std::string strToWrite, LogType type = LOG_INFO, std::string systemName = "Main");
private:
	std::ofstream* FileStream;
	bool IsBad = false;
};
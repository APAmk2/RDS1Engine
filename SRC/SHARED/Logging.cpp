#include <ctime>

#include "Logging.h"

Logger::Logger(std::string name)
{
	FileStream = new std::ofstream(name);
	IsBad = FileStream->bad();
	std::time_t currTime = std::time(nullptr);
	*FileStream << "LOG Started on: " << std::asctime(std::localtime(&currTime)) << std::endl;
}

Logger::~Logger()
{
	std::time_t currTime = std::time(nullptr);
	*FileStream << "LOG Stopped on: " << std::asctime(std::localtime(&currTime)) << std::endl;
	delete FileStream;
}

bool Logger::IsGood()
{
	return FileStream->good();
}

void Logger::WriteLog(std::string strToWrite, LogType type, std::string systemName)
{
	if (IsBad || FileStream->bad()) return;

	if (systemName != "")
	{
		*FileStream << systemName << ": ";
	}

	switch (type)
	{
	case LOG_INFO:
		break;
	case LOG_WARNING:
		*FileStream << "[WARNING] -";
		break;
	case LOG_ERROR:
		*FileStream << "[ERROR] -";
		break;
	case LOG_CRIT_ERROR:
		*FileStream << "[CRITICAL ERROR] -";
		break;
	default:
		break;
	}

	*FileStream << strToWrite;
	*FileStream << std::endl;
}
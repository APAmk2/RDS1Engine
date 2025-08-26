#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <Common.h>
#include <format>

#include "Server.h"

RDS1Server* Server;

int main(int argc, char* args[])
{
	LogMngr = new Logger("RDS1SERV.LOG");
	Server = new RDS1Server;

	LogMngr->WriteLog(std::format("Starting RDS1 Engine, Server. Build No.{}", GetBuildNum(gBuildDate)));

	if (!Server || !Server->Init())
	{
		LogMngr->WriteLog("Failed initialize engine!", LOG_CRIT_ERROR);
	}
	else
	{
		while (!EngineOpts.CallQuit)
		{
			Server->MainLoop();
		}
	}

	delete Server;
	delete LogMngr;

	return 0;
}

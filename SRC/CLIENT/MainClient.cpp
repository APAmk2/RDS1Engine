#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <Common.h>
#include <format>

#include "Client.h"

RDS1Client* Client;

int main(int argc, char* args[])
{
	LogMngr = new Logger("RDS1MAIN.LOG");
	Client = new RDS1Client;

	LogMngr->WriteLog(std::format("Starting RDS1 Engine, Client. Build No.{}", GetBuildNum(gBuildDate)));

	if (!Client || !Client->Init())
	{
		LogMngr->WriteLog("Failed initialize engine!", LOG_CRIT_ERROR);
	}
	else
	{
		while (!EngineOpts.CallQuit)
		{
			Client->MainLoop();
		}
	}

	delete Client;
	delete LogMngr;

	return 0;
}

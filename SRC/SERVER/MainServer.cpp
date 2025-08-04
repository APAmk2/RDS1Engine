#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <Common.h>

#include "Server.h"

RDS1Server* Server;

int main(int argc, char* args[])
{
	Server = new RDS1Server;

	if (!Server || !Server->Init())
	{
		SDL_Log("Failed to initialize!\n");
	}
	else
	{
		while (!EngineOpts.CallQuit)
		{
			Server->MainLoop();
		}
	}

	delete Server;

	return 0;
}

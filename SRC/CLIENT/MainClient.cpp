#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <Common.h>

#include "Client.h"

RDS1Client* Client;

int main(int argc, char* args[])
{
	Client = new RDS1Client;

	if (!Client || !Client->Init())
	{
		SDL_Log("Failed to initialize!\n");
	}
	else
	{
		while (!EngineOpts.CallQuit)
		{
			Client->MainLoop();
		}
	}

	delete Client;

	return 0;
}

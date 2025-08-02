#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Common.h"
#include "Engine.h"

RDS1Engine* Engine;

int main(int argc, char* args[])
{
	Engine = new RDS1Engine;

	if (!Engine || !Engine->Init())
	{
		SDL_Log("Failed to initialize!\n");
	}
	else
	{
		while (!EngineOpts.CallQuit)
		{
			Engine->MainLoop();
		}
	}

	delete Engine;

	return 0;
}

#include <SDL3/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>

#include <Common.h>

#include "Client.h"
#include "OGL/RenderOGL.h"

constexpr int OPENGL_MAJOR = 3;
constexpr int OPENGL_MINOR = 3;
constexpr int OPENGL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
RenderOGL* Render;

bool InitSDL()
{
	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);

	//Create window
	gWindow = SDL_CreateWindow(ENGINE_NAME, EngineOpts.ScreenWidth, EngineOpts.ScreenHeight, SDL_WINDOW_OPENGL);
	if (gWindow == NULL)
	{
		SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Create context
	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == NULL)
	{
		SDL_Log("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_Log("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
	}

	//Use Vsync
	if (!SDL_GL_SetSwapInterval(1))
	{
		SDL_Log("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}

	SDL_StartTextInput(gWindow);

	return true;
}

void DestroySDL()
{
	SDL_StopTextInput(gWindow);
}

RDS1Client::RDS1Client()
{

}
RDS1Client::~RDS1Client()
{
	delete Render;
	Render = NULL;
	DestroySDL();

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool RDS1Client::Init()
{
	if(!InitSDL()) return false;
	Render = new RenderOGL;
	if(!Render || !Render->Init()) return false;

	return true;
}

bool RDS1Client::MainLoop()
{
	static SDL_Event CurrentSDLEvent;
	while (SDL_PollEvent(&CurrentSDLEvent) != 0)
	{
		HandleInput(&CurrentSDLEvent);
	}

	ProcessRender();

	return true;
}

void RDS1Client::HandleInput(SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		EngineOpts.CallQuit = true;
	}

	if (event->type == SDL_EVENT_TEXT_INPUT)
	{
		//Toggle quad
		if (event->text.text[0] == 'q')
		{
			EngineOpts.RenderDemo = !EngineOpts.RenderDemo;
		}
	}

	if (event->type == SDL_EVENT_KEY_DOWN)
	{
		if (event->key.key == SDLK_ESCAPE)
		{
			EngineOpts.CallQuit = true;
		}

		if (event->key.key == SDLK_PAGEUP)
		{
			EngineOpts.CamY += 0.1f;
		}

		if (event->key.key == SDLK_PAGEDOWN)
		{
			EngineOpts.CamY -= 0.1f;
		}

		if (event->key.key == SDLK_UP)
		{
			EngineOpts.CamZ -= 0.1f;
		}

		if (event->key.key == SDLK_DOWN)
		{
			EngineOpts.CamZ += 0.1f;
		}

		if (event->key.key == SDLK_LEFT)
		{
			EngineOpts.CamX -= 0.1f;
		}

		if (event->key.key == SDLK_RIGHT)
		{
			EngineOpts.CamX += 0.1f;
		}
	}
}

bool RDS1Client::ProcessRender()
{
	Render->Process();

	SDL_GL_SwapWindow(gWindow);

	return true;
}
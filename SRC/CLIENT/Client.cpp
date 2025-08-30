#include <SDL3/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>
#include <format>

#include <Common.h>

#include "Client.h"
#include "OGL/RenderOGL.h"
#include "RNDRCOMN/Viewport.h"

#define TOML_EXCEPTIONS 0
#include "toml.hpp"
using namespace std::string_view_literals;

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
		LogMngr->WriteLog(std::format("Failed to initialize SDL! Error: {}", SDL_GetError()), LOG_CRIT_ERROR, "SDL");
		return false;
	}

	LogMngr->WriteLog(std::format("Version: {}.{}, Profile: {}", OPENGL_MAJOR, OPENGL_MINOR, OPENGL_PROFILE), LOG_INFO, "OGL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);

	//Create window
	gWindow = SDL_CreateWindow(ENGINE_NAME, EngineOpts.ScreenWidth, EngineOpts.ScreenHeight, SDL_WINDOW_OPENGL);
	if (gWindow == NULL)
	{
		LogMngr->WriteLog(std::format("Failed to create SDL window! Error: {}", SDL_GetError()), LOG_CRIT_ERROR, "SDL");
		return false;
	}

	//Create context
	gContext = SDL_GL_CreateContext(gWindow);
	if (gContext == NULL)
	{
		LogMngr->WriteLog(std::format("Failed to create OpenGL context! Error: {}", SDL_GetError()), LOG_CRIT_ERROR, "OGL");
		return false;
	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		SDL_Log("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
//		LogMngr->WriteLog(std::format("Failed to initialize GLEW! Error: {}", glewGetErrorString(glewError)), LOG_CRIT_ERROR, "OGL");
	}

	//Use Vsync
	if (!SDL_GL_SetSwapInterval(1))
	{
		LogMngr->WriteLog(std::format("Unable to set VSync! Error {}", SDL_GetError()), LOG_WARNING, "SDL");
	}

	SDL_StartTextInput(gWindow);

	return true;
}

void DestroySDL()
{
	SDL_StopTextInput(gWindow);
}

void LoadConfig()
{
	toml::parse_result result = toml::parse_file("config.toml");
	if (!result)
	{
		LogMngr->WriteLog("Failed to load 'config.toml'!", LOG_WARNING);
		return;
	}
	
	toml::table config = result.table();

	EngineOpts.ScreenWidth = config["Video"]["ScreenWidth"].value_or(640);
	EngineOpts.ScreenHeight = config["Video"]["ScreenHeight"].value_or(480);

	EngineOpts.NetAddr = config["Net"]["ServerAddress"].value_or("localhost"sv);
	EngineOpts.NetPort = config["Net"]["ServerPort"].value_or("27015"sv);

	EngineOpts.RenderDemo = config["Misc"]["RenderDemo"].value_or(true);
}

RDS1Client::RDS1Client()
{
	LogMngr->WriteLog("Created client instance.");
	LoadConfig();
}
RDS1Client::~RDS1Client()
{
	LogMngr->WriteLog("Destroying client.");

	LogMngr->WriteLog("Destroying renderer.", LOG_INFO, "Renderer");
	delete Render;
	Render = NULL;
	DestroySDL();

	LogMngr->WriteLog("Destroying SDL window.", LOG_INFO, "SDL");
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	LogMngr->WriteLog("Destroying SDL.", LOG_INFO, "SDL");
	//Quit SDL subsystems
	SDL_Quit();
}

bool RDS1Client::Init()
{
	LogMngr->WriteLog("Initializing client instance.");

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
			gViewport.Position.y += 0.1f;
		}

		if (event->key.key == SDLK_PAGEDOWN)
		{
			gViewport.Position.y -= 0.1f;
		}

		if (event->key.key == SDLK_UP)
		{
			gViewport.Position.z -= 0.1f;
		}

		if (event->key.key == SDLK_DOWN)
		{
			gViewport.Position.z += 0.1f;
		}

		if (event->key.key == SDLK_LEFT)
		{
			gViewport.Position.x -= 0.1f;
		}

		if (event->key.key == SDLK_RIGHT)
		{
			gViewport.Position.x += 0.1f;
		}
	}
}

bool RDS1Client::ProcessRender()
{
	Render->Process();

	SDL_GL_SwapWindow(gWindow);

	return true;
}
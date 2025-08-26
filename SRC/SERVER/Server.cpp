#include <SDL3/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>
#include <format>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

#include <Common.h>

#include "Server.h"
//#include "OGL/RenderOGL.h"

constexpr int OPENGL_MAJOR = 3;
constexpr int OPENGL_MINOR = 3;
constexpr int OPENGL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;

constexpr int IMGUI_INIT_FLAGS = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable;

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

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

bool InitImGui()
{
	LogMngr->WriteLog(std::format("Initializing ImGUI. Version: {}.", IMGUI_VERSION), LOG_INFO, "ImGUI");

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= IMGUI_INIT_FLAGS;

	ImGui_ImplSDL3_InitForOpenGL(gWindow, gContext);
	ImGui_ImplOpenGL3_Init();

	return true;
}

void DestroyImGui()
{
	LogMngr->WriteLog("Destroying ImGUI.", LOG_INFO, "ImGUI");
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

RDS1Server::RDS1Server()
{
	LogMngr->WriteLog("Created server instance.");
}
RDS1Server::~RDS1Server()
{
	LogMngr->WriteLog("Destroying server.");

	DestroyImGui();
	DestroySDL();

	LogMngr->WriteLog("Destroying SDL window.", LOG_INFO, "SDL");
	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	LogMngr->WriteLog("Destroying SDL.", LOG_INFO, "SDL");
	//Quit SDL subsystems
	SDL_Quit();
}

bool RDS1Server::Init()
{
	LogMngr->WriteLog("Initializing server instance.");

	if(!InitSDL()) return false;
	if(!InitImGui()) return false;
	//Render = new RenderOGL;
	//if(!Render || !Render->Init()) return false;

	return true;
}

bool RDS1Server::MainLoop()
{
	static SDL_Event CurrentSDLEvent;

	while (SDL_PollEvent(&CurrentSDLEvent) != 0)
	{
		HandleInput(&CurrentSDLEvent);
	}

	ProcessRender();

	return true;
}

void RDS1Server::HandleInput(SDL_Event* event)
{
	if(ImGui_ImplSDL3_ProcessEvent(event)) return;
	if (event->type == SDL_EVENT_QUIT)
	{
		EngineOpts.CallQuit = true;
	}

	if (event->type == SDL_EVENT_KEY_DOWN)
	{

	}
}

bool RDS1Server::ProcessRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_GL_SwapWindow(gWindow);

	return true;
}
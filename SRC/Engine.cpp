#include <SDL3/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <string>

#include "Common.h"
#include "Engine.h"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

constexpr int OPENGL_MAJOR = 3;
constexpr int OPENGL_MINOR = 1;
constexpr int OPENGL_PROFILE = SDL_GL_CONTEXT_PROFILE_CORE;

constexpr char WINDOW_LABEL[] = "RDS1 Engine";

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

// Dummy shit from example - APAMk2
bool gRenderQuad = true;

bool InitOGL()
{
	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		SDL_Log("Unable to compile vertex shader %d!\n", vertexShader);
		//printShaderLog(vertexShader);
		return false;
	}
	//Attach vertex shader to program
	glAttachShader(gProgramID, vertexShader);


	//Create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Get fragment source
	const GLchar* fragmentShaderSource[] =
	{
		"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
	};

	//Set fragment source
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

	//Compile fragment source
	glCompileShader(fragmentShader);

	//Check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
		SDL_Log("Unable to compile fragment shader %d!\n", fragmentShader);
		//printShaderLog(fragmentShader);
		return false;
	}

	//Attach fragment shader to program
	glAttachShader(gProgramID, fragmentShader);

	//Link program
	glLinkProgram(gProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		SDL_Log("Error linking program %d!\n", gProgramID);
		//printProgramLog(gProgramID);
		return false;
	}
	//Get vertex attribute location
	gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
	if (gVertexPos2DLocation == -1)
	{
		SDL_Log("LVertexPos2D is not a valid glsl program variable!\n");
		return false;
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//VBO data
	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f,  0.5f,
		-0.5f,  0.5f
	};

	//IBO data
	GLuint indexData[] = { 0, 1, 2, 3 };

	//Create VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//Create IBO
	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	return true;
}

bool InitSDL()
{
	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, OPENGL_PROFILE);

	//Create window
	gWindow = SDL_CreateWindow(WINDOW_LABEL, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
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

void KillSDL()
{
	SDL_StopTextInput(gWindow);
}

RDS1Engine::RDS1Engine()
{

}
RDS1Engine::~RDS1Engine()
{
	KillSDL();

	//Deallocate program
	glDeleteProgram(gProgramID);

	//Destroy window	
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool RDS1Engine::Init()
{
	if(!InitSDL()) return false;
	if(!InitOGL()) return false;

	return true;
}

bool RDS1Engine::MainLoop()
{
	static SDL_Event CurrentSDLEvent;
	while (SDL_PollEvent(&CurrentSDLEvent) != 0)
	{
		HandleInput(&CurrentSDLEvent);
	}

	ProcessRender();

	return true;
}

void RDS1Engine::HandleInput(SDL_Event* event)
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
			gRenderQuad = !gRenderQuad;
		}
	}

	if (event->type == SDL_EVENT_KEY_DOWN)
	{
		if (event->key.key == SDLK_ESCAPE)
		{
			EngineOpts.CallQuit = true;
		}
	}
}

void render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	if (!gRenderQuad) return;

	//Bind program
	glUseProgram(gProgramID);

	//Enable vertex position
	glEnableVertexAttribArray(gVertexPos2DLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);

	//Unbind program
	glUseProgram(0);
}

bool RDS1Engine::ProcessRender()
{
	render(); // Dummy func from example, at least for now - APAMk2

	SDL_GL_SwapWindow(gWindow);

	return true;
}

/*void printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			SDL_Log("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		SDL_Log("Name %d is not a shader\n", shader);
	}
}

void printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			SDL_Log("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		SDL_Log("Name %d is not a program\n", program);
	}
}*/
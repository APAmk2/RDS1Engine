#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <GL/glu.h>
#include <vector>

#include "../Common.h"
#include "ShaderOGL.h"

ShaderOGL::ShaderOGL(std::string sources, GLuint type)
{
	ID = glCreateShader(type);
	const char* sourcePtr = sources.c_str();
	glShaderSource(ID, 1, &sourcePtr, NULL);
	glCompileShader(ID);

	int InfoLogLength;

	glGetShaderiv(ID, GL_COMPILE_STATUS, &IsValid);
	glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}
}

ShaderOGL::~ShaderOGL()
{
	if (IsValid == GL_FALSE) return;

	glDeleteShader(ID);
}

ShaderProgramOGL::ShaderProgramOGL(ShaderVec shaders)
{
	ID = glCreateProgram();
	for (auto it = shaders.begin(), end = shaders.end(); it != end; ++it)
	{
		ShaderOGL* shader = *it;
		glAttachShader(ID, shader->ID);
	}
	glLinkProgram(ID);

	int InfoLogLength;

	glGetProgramiv(ID, GL_LINK_STATUS, &IsValid);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
}
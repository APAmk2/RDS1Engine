#pragma once

#include <string>
#include <vector>

class ShaderOGL
{
public:
	GLuint ID = 0;
	GLuint Type = GL_VERTEX_SHADER;
	GLint IsValid = GL_FALSE;

	ShaderOGL(std::string sources, GLuint type);
	~ShaderOGL();
};

typedef std::vector<ShaderOGL*> ShaderVec;

class ShaderProgramOGL
{
public:
	GLuint ID = 0;
	GLint IsValid = GL_FALSE;

	ShaderProgramOGL(ShaderVec shaders);
private:
//	ShaderVec Shaders;
};
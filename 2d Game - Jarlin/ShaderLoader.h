#ifndef SHADERLOADER_H
#define SHADERLOADER_H

// Libraries
#include "glew.h"
#include "freeglut.h"
#include <iostream>

class ShaderLoader
{
public:
	ShaderLoader(void);
	~ShaderLoader(void);
	GLuint CreateProgram(char* VertexShaderFilename,
						 char* FragmentShaderFilename);

private:
	std::string ReadShader(char *filename);
	GLuint CreateShader(GLenum shaderType,
		std::string source,
		char* shaderName);
};

#endif // SHADERLOADER_H
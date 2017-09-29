#include "Shader.h"
#include <iostream>
#include <string>
#include "gl_core_4_4.h"
#include <fstream>

ShaderApplication::ShaderApplication()
{	
}

ShaderApplication::~ShaderApplication()
{
}

void ShaderApplication::bind()
{
	glUseProgram(m_program);

}

void ShaderApplication::unbind() 
{
	glUseProgram(0);

}

void ShaderApplication::load(const char * filename, unsigned int type)
{
	std::string line, contents;
	std::ifstream in(filename);

	// while file is not empty
	while (std::getline(in, line))
	{
		//add that line to the total contents
		contents += line + "\n";
	}

	// convert to a c-string
	const char * data = contents.c_str();

	switch (type)
	{
	case GL_VERTEX_SHADER:
		m_vsSource = data;
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(m_vertexShader, 1, (const char **)&m_vsSource, 0);
		glCompileShader(m_vertexShader);

	case GL_FRAGMENT_SHADER:
		m_fsSource = data;
		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(m_fragmentShader, 1, (const char **)&m_fsSource, 0);
		glCompileShader(m_fragmentShader);

	}
}

void ShaderApplication::attach()
{
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);
	int success = GL_FALSE;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
		printf("Error: Failed to link shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}
	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}

void ShaderApplication::defaultLoad()
{
	//m_vsSource = "#version 410\n \
	//layout(location=0) in vec4 position; \
	//layout(location=1) in vec4 Colour; \
	//out vec4 vColour; \
	//uniform mat4 projectionViewWorldMatrix; \
	//void main() { vColour = Colour; gl_Position =\
	//projectionViewWorldMatrix * position; }";
	//
	//m_fsSource = "#version 410\n \
	//in vec4 vColour; \
	//out vec4 fragColour;\
	//void main() { fragColour = vColour; }";

	

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, (const char**)&m_vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&m_fsSource, 0);
	glCompileShader(m_fragmentShader);

 
}

unsigned int ShaderApplication::getUniform(const char* name)
{
	return glGetUniformLocation(m_program, name);
}
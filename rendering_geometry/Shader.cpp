#include "Shader.h"
#include <iostream>
#include <cstring>
#include "gl_core_4_4.h"

Shader::Shader()
{	
}

Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(m_program);

}

void Shader::unbind() 
{
	glUseProgram(0);

}

void Shader::load(const char * filename, unsigned int type)
{

	
}

void Shader::attach()
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

void Shader::defaultLoad()
{
	m_vsSource = "#version 410\n \
							layout(location=0) in vec4 Pos; \
							layout(location=1) in vec4 Color; \
							out vec4 vColour; \
							uniform mat4 mvp; \
							void main(){vColour = Color; gl_Position = mvp * Pos;}";

	m_fsSource = "#version 410\n \
							in vec4 vColour; \
							out vec4 fragColor; \
							void main(){fragColor = vColour;}";

	

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, (const char**)&m_vsSource, 0);
	glCompileShader(m_vertexShader);
	glShaderSource(m_fragmentShader, 1, (const char**)&m_fsSource, 0);
	glCompileShader(m_fragmentShader);
}

unsigned int Shader::getUniform(const char* name)
{
	return glGetUniformLocation(m_program, name);
}
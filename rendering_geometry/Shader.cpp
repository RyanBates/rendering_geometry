#include "Shader.h"
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

}

void Shader::unbind() 
{

}

void Shader::load(const char * filename, unsigned int type)
{
	glUseProgram(m_program);

}

void Shader::attach()
{

}

void Shader::defaultLoad()
{

}

unsigned int Shader::getUniform(const char *)
{


	return 0;
}

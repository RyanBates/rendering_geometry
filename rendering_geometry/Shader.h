#pragma once
class ShaderApplication
{
public:
	ShaderApplication();
	~ShaderApplication();

	void bind();
	void unbind();

	void load(const char * filename, unsigned int type);
	void attach();
	void defaultLoad();
	unsigned int getUniform(const char *);
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	const char* m_vsSource;
	const char* m_fsSource;


	unsigned int m_program;
};
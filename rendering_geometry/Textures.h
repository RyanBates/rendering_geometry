#pragma once
#include "Application.h"
class Mesh;
class Shader;
class Geo;

class Textures : public Application
{
public:
	Textures();
	virtual ~Textures();

	void load(const char * filename, unsigned int width, unsigned int height);


	void startup();
	void draw();
	void update(float);
	void shutdown(); 


private:
	unsigned int m_texture;
	unsigned int m_program;

	
	Shader* shade;
	Mesh* mesh;
	Geo* geo;
	Textures* text;
};


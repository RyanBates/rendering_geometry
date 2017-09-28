#pragma once
#include "Application.h"
class Mesh;
class Shader;

class Textures : public Application
{
public:
	Textures();
	virtual ~Textures();

	void load();

	void startup();
	void draw();
	void update(float);
	void shutdown(); 
	
	unsigned int m_texture;	
		
	Shader* shade;
	Mesh* mesh;
};


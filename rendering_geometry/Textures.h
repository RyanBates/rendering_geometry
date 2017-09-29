#pragma once
#include "Application.h"
class MeshApplication;
class ShaderApplication;

class TextureApplication : public Application
{
public:
	TextureApplication();
	virtual ~TextureApplication();

	void load();

	void startup();
	void draw();
	void update(float);
	void shutdown(); 
	
	unsigned int m_texture;	
		
	ShaderApplication* shade;
	MeshApplication* mesh;
};


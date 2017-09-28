#pragma once
#include <Application.h>
#include <glm\glm.hpp>

class Shader;
class Mesh;
class Textures;
struct Vertex;

using namespace glm;
using namespace std;

class Geo : public Application
{
public:
	Geo();
	~Geo();

	void startup();
	void shutdown();
	void update(float);
	void draw();
	

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionView;

	Shader * shade;
	Mesh* mesh;
	Textures* text;

};
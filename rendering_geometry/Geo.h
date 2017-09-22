#pragma once
#include <Application.h>
#include <glm\glm.hpp>
class Shader;
class Mesh;
struct Vertex;
struct Lighting;
struct Material;

using namespace glm;
using namespace std;

class Geo : public Application
{
public:
	Geo();
	~Geo();

	void generateGrid(unsigned int rows, unsigned int cols);
	void startup();
	void shutdown();
	void update(float);
	void draw();
	
	unsigned int m_programID;

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionView;

	Shader * shade;
	Mesh* mesh;
};
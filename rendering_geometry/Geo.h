#pragma once
#include <Application.h>
#include <glm\glm.hpp>
using namespace glm;
using namespace std;

struct Vertex {
	vec4 Position;
	vec4 Color;
};

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

	vector<vec4> GenHalfCircle(int, int);
	vector<vec4> GenSphere(vector<vec4>, int);

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_programID;

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionViewUniform;

};


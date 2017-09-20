#pragma once
#include <Application.h>
#include <glm\glm.hpp>
class Shader;
class Mesh;
struct Vertex;

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

	//vector<vec4> GenHalfCircle(unsigned int, unsigned int);
	//vector<vec4> GenSphere(vector<vec4>, unsigned int);

	//unsigned int m_VAO;
	//unsigned int m_VBO;
	//unsigned int m_IBO;

	unsigned int m_programID;

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionViewUniform;

	Shader * m_shader;
	Shader& TheShader;
	Mesh* m_mesh;
};
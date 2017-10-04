#pragma once
#include <Application.h>
#include <glm\glm.hpp>

class ShaderApplication;
class MeshApplication;
class TextureApplication;
struct Vertex;

using namespace glm;
using namespace std;

class GeometryApplication : public Application
{
public:
	GeometryApplication();
	~GeometryApplication();

	void perlin(double x, double y, double z);

	void startup();
	void shutdown();
	void update(float);
	void draw();
	

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionView;

	ShaderApplication * shade;
	MeshApplication* mesh;
	TextureApplication* text;

};
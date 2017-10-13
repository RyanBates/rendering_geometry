#pragma once
#include <Application.h>
#include <glm\glm.hpp>

class ShaderApplication;
class MeshApplication;
class TextureApplication;
class CameraApplication;
class FlyCamera;
struct Vertex;

using namespace glm;
using namespace std;

class GeometryApplication : public Application
{
public:
	GeometryApplication();
	~GeometryApplication();

	void startup();
	void shutdown();
	void update(float);
	void draw();
	

	unsigned int rows;
	unsigned int cols;

	mat4 m_projectionView;


	Application* app;
	ShaderApplication * shade;
	MeshApplication* mesh;
	TextureApplication* text;
	CameraApplication* cam;
	FlyCamera* f_cam;

};
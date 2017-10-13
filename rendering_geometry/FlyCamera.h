#pragma once
#include "Camera.h"
#include "gl_core_4_4.h"
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>
#include <GLFW\glfw3.h>
#include <Gizmos.h>
using namespace glm;

class FlyCamera : public CameraApplication
{
public:
	FlyCamera();
	~FlyCamera();

	float speed;

	vec3 up;

	void startup();
	void draw();
	void shutdown();

	void update(float deltaTime);
	void setSpeed(float speed);
};


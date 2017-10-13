#pragma once
#include "Application.h"
#include "gl_core_4_4.h"
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>
#include <Gizmos.h>
using namespace glm;

class CameraApplication : public Application
{
public:
	CameraApplication();
	~CameraApplication();

	vec3 pos;

	void update(float deltaTime) = 0;
	void setPosition(vec3 position);
	
	mat4 getWorldTransform();
	mat4 getView();
	mat4 getProjection();
	mat4 getProjectionView();

};


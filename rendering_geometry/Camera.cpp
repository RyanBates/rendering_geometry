#include "Camera.h"

CameraApplication::CameraApplication()
{
}

CameraApplication::~CameraApplication()
{
}

void CameraApplication::setPosition(vec3 position)
{
	
}

//mat4 Camera::getWorldTransform()
//{
//	mat4 worldTransform;
//
//	return worldTransform;
//}

mat4 CameraApplication::getView()
{
	vec3 pos(10, 10, 10);

	mat4 viewTransform = lookAt(pos, vec3(0), vec3(0, 1, 0));

	return viewTransform;
}

mat4 CameraApplication::getProjection()
{
	mat4 projectionTransform = perspective(quarter_pi<float>(), 16.f / 9.f, .1f, 1000.f);

	return projectionTransform;
}

mat4 CameraApplication::getProjectionView()
{
	mat4 projectionView = getProjection() * getView();

	return projectionView;
}
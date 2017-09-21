#include "Camera.h"

Camera::~Camera()
{
}

void Camera::update(float dT)
{
}

void Camera::setPerspective(float fieldOfView, float aspectRatio, float near, float far)
{

}

void Camera::setLookAt(vec3 eye, vec3 center, vec3 up)
{
	vec3 f_right = eye - center;
	vec3 f_up = f_right / normalize(f_right);

	vec3 z = f_up;
	vec3 s_right = cross(up, z);

	vec3 x = s_right / normalize(s_right);
	vec3 u = cross(z, x);

	vec3 y = u / normalize(u);

}

void Camera::setpos(vec3 pos)
{
}

mat4 Camera::getWorldTransform()
{
	return mat4();
}

mat4 Camera::getView()
{
	return mat4();
}

mat4 Camera::getProjection()
{
	return mat4();
}

mat4 Camera::getProjectionView()
{
	return mat4();
}
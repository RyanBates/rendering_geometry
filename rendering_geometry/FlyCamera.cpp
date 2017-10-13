#include "FlyCamera.h"
#include<iostream>

FlyCamera::FlyCamera()
{
}


FlyCamera::~FlyCamera()
{
}

void FlyCamera::startup()
{

}

void FlyCamera::draw()
{

}

void FlyCamera::shutdown()
{

}

void FlyCamera::update(float deltaTime)
{
	float currentTime = (float)glfwGetTime();
	float previousTime = currentTime;
	deltaTime = currentTime - previousTime; // prev of last frame
	/*
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		pos += vec3(0, 0, 5);
		std::printf("was hit");
	}
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		pos -= vec3(5, 0, 0);

	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		pos -= vec3(0, 0, 5);

	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		pos += vec3(5, 0, 0);

	if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
		pos -= vec3(0, 5, 0);

	if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
		pos += vec3(0, 5, 0);
	*/
}

void FlyCamera::setSpeed(float speed)
{

}

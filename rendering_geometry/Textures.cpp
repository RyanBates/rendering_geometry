#include "Textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include "Shader.h"
#include "Mesh.h"

Textures::Textures()
{
	shade = new Shader();
	mesh = new Mesh();
}

Textures::~Textures()
{
}

void Textures::load()
{


	int imageWidth = 0, imageHeight = 0, imageFormat = 0;
	int imageWidth2 = 0, imageHeight2 = 0, imageFormat2 = 0;

	unsigned char* data = stbi_load("./Textures/crate.png", &imageWidth, &imageHeight, &imageFormat, STBI_default);
	unsigned char* data2 = stbi_load("./Textures/morals.png", &imageWidth2, &imageHeight2, &imageFormat2, STBI_default);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth , imageHeight , 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
	

}

void Textures::startup()
{
}

void Textures::draw()
{
}

void Textures::update(float)
{
}

void Textures::shutdown()
{
}

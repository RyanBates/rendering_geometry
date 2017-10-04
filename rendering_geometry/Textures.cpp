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

TextureApplication::TextureApplication()
{
	shade = new ShaderApplication();
	mesh = new MeshApplication();
}

TextureApplication::~TextureApplication()
{
}

void TextureApplication::load()
{


	int imageWidth = 0, imageHeight = 0, imageFormat = 0;

	unsigned char* data = stbi_load("./Textures/earth.jpg", &imageWidth, &imageHeight, &imageFormat, STBI_default);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth , imageHeight , 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
	

}

void TextureApplication::startup()
{
}

void TextureApplication::draw()
{
}

void TextureApplication::update(float)
{
}

void TextureApplication::shutdown()
{
}

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

	unsigned char* data = stbi_load("./Textures/crate.png", &imageWidth, &imageHeight, &imageFormat, STBI_default);

	/// AIE's perlin noise function
	int dims = 64;
	float *perlinData = new float[dims * dims];
	float scale = (1.0f / dims) * 3;
	int octaves = 6;
	for (int x = 0; x < 64; ++x)
		for (int y = 0; y < 64; ++y)
		{
			float amplitude = 1.f;
			float persistence = 0.3f;
			perlinData[y * dims + x] = 0;
			for (int o = 0; o < octaves; ++o)
			{
				float freq = powf(2, o);
				float perlinSample = glm::perlin(vec2((float)x, (float)y) * scale * freq) * .5 + .5;
				perlinData[y * dims + x] += perlinSample * amplitude;
				amplitude *= persistence;
			}
		}




	//glGenTextures(1, &m_texture);
	//glBindTexture(GL_TEXTURE_2D, m_texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth , imageHeight , 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &m_perlinTexture);
	glBindTexture(GL_TEXTURE_2D, m_perlinTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, 64, 64, 0, GL_RED, GL_FLOAT, perlinData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



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

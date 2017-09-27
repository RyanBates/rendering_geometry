#include "Textures.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "gl_core_4_4.h"
#include "Shader.h"
#include "Mesh.h"
#include "Geo.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>


Textures::Textures()
{
	//shade = new Shader();
	//mesh = new Mesh();
	//geo = new Geo();
}

Textures::~Textures()
{
}

void Textures::load(const char * filename, unsigned int width, unsigned int height)
{
	int imageWidth, imageHeight, imageFormat = 0;

	unsigned char* data = stbi_load("./Textures/crate.png", &imageWidth, &imageHeight, &imageFormat, STBI_rgb);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight,	0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);

	const char* vsSource = "#version 410\n \
							layout(location=0) in vec4 position; \
							layout(location=1) in vec2 texCoord; \
							out vec2 vTexCoord; \
							uniform mat4 projectionViewWorldMatrix; \
							void main() { \
							vTexCoord = texCoord; \
							gl_Position= projectionViewWorldMatrix * position; }";

	const char* fsSource = "#version 410\n \
							in vec2 vTexCoord; \
							out vec4 fragColor; \
							uniform sampler2D diffuse; \
							void main() { \
							fragColor = texture(diffuse,vTexCoord); }";

	//mesh->create_buffers();

}

void Textures::startup()
{
	auto eye = vec3(10, 10, 10);
	auto center = vec3(0);
	auto up = vec3(0, 1, 0);

	auto projection = perspective(quarter_pi<float>(), 16.f / 9.f, .1f, 1000.f);
	auto view = lookAt(eye, center, up);

	geo->m_projectionView = projection * view;

	float vertexData[] = 
	{
		-5, 0, 5, 1, 0, 1,
		5, 0, 5, 1, 1, 1,
		5, 0, -5, 1, 1, 0,
		-5, 0, -5, 1, 0, 0,
	};
	unsigned int indexData[] = 
	{
		0, 1, 2,
		0, 2, 3,
	};

	load("./Textures/crate.png", vertexData[0], indexData[0]);
}

void Textures::draw()
{
	auto trans = mat4(1);
	trans = translate(trans, vec3(0, 0, 0));
	auto mvp = geo->m_projectionView * trans;

	glUseProgram(m_program);
	// bind the camera
	int loc = glGetUniformLocation(m_program, "projectionViewWorldMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(mvp));
	// set texture slot
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	// tell the shader where it is
	loc = glGetUniformLocation(m_program, "diffuse");
	glUniform1i(loc, 0);
	// draw
	glBindVertexArray(mesh->m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Textures::update(float)
{
}

void Textures::shutdown()
{
}

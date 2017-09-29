#include "Geo.h"
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "Textures.h"
#include <iostream>

#define PI 3.14159265359

GeometryApplication::GeometryApplication()
{
	shade = new ShaderApplication();
	mesh = new MeshApplication();
	text = new TextureApplication();
}

GeometryApplication::~GeometryApplication()
{
}

vector<vec4> generateHalfCircle(int r, int np)
{
	vector<vec4> half = vector<vec4>(np);

	for (float i = 0; i < np; ++i)
	{
		float angle = PI / (np - 1);

		float theta = angle * i;

		half[i].x = sin(theta) * r;
		half[i].y = cos(theta) * r;
		half[i].z = 0.f;
		half[i].w = 1.f;
	}

	return half;
}

vector<vec4> genSphere(vector<vec4> np, int nm)
{
	vector<vec4> sphere;

	for (int i = 0; i <= nm; i++)
	{
		float slice = (2.f * PI) / nm;
		float phi = i * slice;

		for (int j = 0; j < np.size(); j++)
		{
			float newX = np[j].x * cos(phi) + np[j].z * sin(phi);
			float newY = np[j].y;
			float newZ = np[j].z* cos(phi) - np[j].x * sin(phi);

			sphere.push_back(vec4(newX, newY, newZ, 1.f));
		}
	}

	return sphere;
}

vector<unsigned int> sphereIndinces(unsigned int nm, unsigned int np)
{

	Vertex* vertex;

	vector<unsigned int> rotate;

	unsigned int start;
	unsigned int botLeft;
	unsigned int botRight;

	for (int i = 0; i < nm; i++)
	{
		start = i * np;

		for (int j = 0; j < np; j++)
		{
			botLeft = start + j;
			botRight = botLeft + np;
			rotate.push_back(botLeft);
			rotate.push_back(botRight);

		}
		rotate.push_back(0xffff);
	}
	
	return rotate;
}

void generateSphere(unsigned int segments, unsigned int rings,	unsigned int& vao, unsigned int& vbo, unsigned int& ibo, unsigned int& indexCount) 
{
	unsigned int vertCount = (segments + 1) * (rings + 2);
	indexCount = segments * (rings + 1) * 6;

	// using AIEVertex for now, but could be any struct as long as it has the correct elements
	Vertex* vertices = new Vertex[vertCount];
	unsigned int* indices = new unsigned int[indexCount];

	float ringAngle = glm::pi<float>() / (rings + 1);
	float segmentAngle = 2.0f * glm::pi<float>() / segments;

	Vertex* vertex = vertices;

	for (unsigned int ring = 0; ring < (rings + 2); ++ring) {
		float r0 = glm::sin(ring * ringAngle);
		float y0 = glm::cos(ring * ringAngle);

		for (unsigned int segment = 0; segment < (segments + 1); ++segment, ++vertex) {
			float x0 = r0 * glm::sin(segment * segmentAngle);
			float z0 = r0 * glm::cos(segment * segmentAngle);

			vertex->position = glm::vec4(x0 * 0.5f, y0 * 0.5f, z0 * 0.5f, 1);
			vertex->normal = glm::vec4(x0, y0, z0, 0);

			vertex->tangent = glm::vec4(glm::sin(segment * segmentAngle + glm::half_pi<float>()), 0, glm::cos(segment * segmentAngle + glm::half_pi<float>()), 0);

			// not a part of the AIEVertex, but this is how w generate bitangents
			vertex->bitangent = glm::vec4(glm::cross(glm::vec3(vertex->normal), glm::vec3(vertex->tangent)), 0);

			vertex->texcoord = glm::vec2(segment / (float)segments, ring / (float)(rings + 1));
		}
	}

	unsigned int index = 0;
	for (unsigned i = 0; i < (rings + 1); ++i) {
		for (unsigned j = 0; j < segments; ++j) {
			indices[index++] = i * (segments + 1) + j;
			indices[index++] = (i + 1) * (segments + 1) + j;
			indices[index++] = i * (segments + 1) + (j + 1);

			indices[index++] = (i + 1) * (segments + 1) + (j + 1);
			indices[index++] = i * (segments + 1) + (j + 1);
			indices[index++] = (i + 1) * (segments + 1) + j;
		}
	}

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	// generate vertex array object (descriptors)
	glGenVertexArrays(1, &vao);

	// all changes will apply to this handle
	glBindVertexArray(vao);

	// set vertex buffer data
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// index data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4)));

	// normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 2));

	// texcoords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3));

	// tangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)(sizeof(glm::vec4) * 3 + sizeof(glm::vec2)));

	// safety
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] indices;
	delete[] vertices;
}

void GeometryApplication::startup()
{
	auto eye = vec3(15, 15, 15);
	auto center = vec3(0);
	auto up = vec3(0, 1, 0);

	//auto projection = perspective(quarter_pi<float>(), 16.f / .9f, .1f, 1000.f);
	auto projection = glm::perspective(quarter_pi<float>(), 16.f / 9.f, .1f, 1000.f);
	auto view = glm::lookAt(eye, center, up);

	m_projectionView = projection * view;

	shade->load("./Shaders/phong.vert", GL_VERTEX_SHADER);
	shade->load("./Shaders/phong.frag", GL_FRAGMENT_SHADER);

	
	text->load();

	shade->attach();

	vec4 p;
	///indinces for plane
	//Vertex a = { p = vec4(0,0,0,1), vec4(0,0,0,1), normalize(p), vec2(0,0) };
	//Vertex b = { p = vec4(5,0,0,1), vec4(0,0,0,1), normalize(p), vec2(1,0) };
	//Vertex c = { p = vec4(0,0,5,1), vec4(0,0,0,1), normalize(p), vec2(0,1) };
	//Vertex d = { p = vec4(5,0,5,1), vec4(0,0,0,1), normalize(p), vec2(1,1) };

	//std::vector<Vertex> vertices{ a,b,c,d };
	//std::vector<unsigned int> indices{ 0, 1, 2, 3 };

	
	//mesh->initialize(vertices, indices);
	//mesh->create_buffers();
	
	/// indinces for sphere
	vector<Vertex> ver;
	vector<unsigned int> uints;

	int r = 5;
	int np = 60;
	int nm = 60;

	vector<vec4>halfcircle = generateHalfCircle(r, np);

	vector<vec4>sphere = genSphere(halfcircle, nm);

	uints = sphereIndinces(nm, np);

	for (auto p : sphere)
	{		
		Vertex vert = { p, vec4(1), normalize(p), vec2(-p.x / (np - 55), -p.y / (nm - 55)) };
		ver.push_back(vert);	
	}
			
	mesh->initialize(ver, uints);
	mesh->create_buffers();

	///matthew's sphere function
	//unsigned int i = 100;
	//unsigned int j = 100;

	//generateSphere(i, j, mesh->m_VAO, mesh->m_VBO, mesh->m_IBO, mesh->m_index_count);
}

float specularPower = 10;
float red = 0;
float green= 0;
float blue = 0;

float lightDirX = 5;
float lightDirY = 5;
float lightDirZ = 5;

void GeometryApplication::draw()
{
	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Begin("Light");
	ImGui::SliderFloat("spec power", &specularPower, 10, 255);
	ImGui::SliderFloat("light direction x axis", &lightDirX, -10.f, 10.f);
	ImGui::SliderFloat("light direction y axis", &lightDirY, -10.f, 10.f);
	ImGui::SliderFloat("light direction z axis", &lightDirZ, -10.f, 10.f);
	ImGui::End();

	shade->bind();
	
	unsigned handle = shade->getUniform("projectionViewWorldMatrix");
	
	mesh->bind();

	auto trans = mat4(1);
	trans = translate(trans, vec3(0));
	auto mvp = m_projectionView * trans;
	
	glUniformMatrix4fv(handle, 1, false, value_ptr(mvp));

	glUniform1f(shade->getUniform("specularPower"), specularPower);
	glUniform1f(shade->getUniform("LDX"), lightDirX);
	glUniform1f(shade->getUniform("LDY"), lightDirY);
	glUniform1f(shade->getUniform("LDZ"), lightDirZ);

	glDrawElements(GL_TRIANGLE_STRIP, mesh->m_index_count, GL_UNSIGNED_INT, 0);
	mesh->unbind();
	shade->unbind();	
}

void GeometryApplication::update(float)
{	
	
}

void GeometryApplication::shutdown()
{
}
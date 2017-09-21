

#include "Geo.h"
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
#include<glm\glm.hpp>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <vector>
#include "Shader.h"
#include "Mesh.h"

float PI = 3.14159265359;

Geo::Geo()
{
	shade = new Shader();
	mesh = new Mesh();
}

Geo::~Geo()
{
}
//
//void Geo::generateGrid(unsigned int rows, unsigned int cols)
//{
//	//this is what gives the color to the objects.
//	Vertex* aoVertices = new Vertex[rows * cols];
//
//	for (unsigned int r = 0; r < rows; ++r)
//		for (unsigned int c = 0; c < cols; ++c)
//		{
//			aoVertices[r * cols + c].Position = vec4((float)c, 0, (float)r, 1);
//			// create some arbitrary colour based off something
//			// that might not be related to tiling a texture
//			vec3 colour = vec3(sinf((c / (float)(cols - 1))* (r / (float)(rows - 1))));
//			aoVertices[r * cols + c].Color = vec4(colour, 1);
//		}
//
//	//this is what will give the points to the trangles.
//	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
//
//	unsigned int index = 0;
//	for (unsigned int r = 0; r<(rows - 1); ++r)
//		for (unsigned int c = 0; c < (cols - 1); ++c)
//		{
//			//tri 1
//			auiIndices[index++] = r * cols + c;
//			auiIndices[index++] = (r + 1) * cols + c;
//			auiIndices[index++] = (r + 1) * cols + (c + 1);
//			//tri2
//			auiIndices[index++] = r * cols + c;
//			auiIndices[index++] = (r + 1)* cols + (c + 1);
//			auiIndices[index++] = r * cols + (c + 1);
//		}
//
//
//	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
//
//		
//	delete[] aoVertices;
//	delete[] auiIndices;
//}

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

	for (int i = 0; i < nm; ++i)
	{
		float slice = (2 * PI) / nm;
		float phi = i * slice;

		for (int j = 0; j < np.size(); ++j)
		{
			float newX = np[j].x * sin(phi) * np[j].z * cos(phi);
			float newY = np[j].y;
			float newZ = np[j].z* cos(phi) * np[j].x * sin(phi);

			sphere.push_back(vec4(newX, newY, newZ, 1.f));
		}
	}

	return sphere;
}

vector<unsigned int> sphereIndinces(unsigned int nm, unsigned int np)
{
	vector<unsigned int> rotate;

	unsigned int start;
	unsigned int botLeft;
	unsigned int botRight;

	for (int i = 0; i < nm; ++i)
	{
		start = i * np;

		for (int j = 0; j < np; ++j)
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
unsigned VAO, VBO, IBO, INDEXCOUNT;
void Geo::startup()
{
	auto eye = vec3(10, 10, 5);
	auto center = vec3(0);
	auto up = vec3(0, 1, 0);

	//auto projection = perspective(quarter_pi<float>(), 16.f / .9f, .1f, 1000.f);
	auto projection = glm::perspective(quarter_pi<float>(), 16.f / 9.f, .1f, 1000.f);
	auto view = glm::lookAt(eye, center, up);

	m_projectionView = projection * view;


	//loading from the shader class

	//m_shader->load("./Shaders/phong.vert", GL_VERTEX_SHADER);
	//m_shader->load("./Shaders/phong.frag", GL_FRAGMENT_SHADER);

	shade->defaultLoad();
	shade->attach();


	//this is to populate 


	/// indinces for plane

	///matthew's plane
	//Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) };//bl	
	//Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//br
	//Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//tl
	//Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) };//tr
	//Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) };//tr	

	//std::vector<Vertex> vertices{ a,b,c,d,e };
	//std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };

	/// indinces for cube

	/// indinces for sphere
	//vector<Vertex> ver;
	//vector<unsigned int> uints;

	//int r = 2;
	//int np = 5;
	//int nm = 4;

	//vector<vec4>halfcircle = generateHalfCircle(r, np);

	//vector<vec4>sphere = genSphere(halfcircle, nm);

	//uints = sphereIndinces(nm, np);

	//for (auto p : sphere)
	//{
	//	Vertex vert = { p, vec4(.75f, 0, .75f, 1) };
	//	ver.push_back(vert);
	//}

	//mesh->initialize(ver, uints);

	///matthew's call function
	unsigned int i = 100;
	unsigned int j = 100;

	generateSphere(i, j, mesh->m_VAO, mesh->m_VBO, mesh->m_IBO, mesh->m_index_count);
}

void Geo::draw()
{
	
	ImGui_ImplGlfwGL3_NewFrame();
	shade->bind();
	
	unsigned handle = shade->getUniform("projectionViewWorldMatrix");
	
	glUniformMatrix4fv(handle, 1, false, value_ptr(m_projectionView));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, INDEXCOUNT, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	mesh->bind();
	auto trans = glm::mat4(1);
	trans = translate(trans, vec3(0, 0, 0));
	auto mvp = m_projectionView * trans;
	glUniformMatrix4fv(handle, 1, false, value_ptr(mvp));
	glDrawElements(GL_TRIANGLES, mesh->m_index_count, GL_UNSIGNED_INT, 0);
	mesh->unbind();
	shade->unbind();

	
}

void Geo::update(float)
{	
}

void Geo::shutdown()
{
}
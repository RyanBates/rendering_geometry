#pragma once
#include "Geo.h"
#include <vector>
#include <glm\glm.hpp>

struct Vertex {
	vec4 Position;
	vec4 Color;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void create_buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);

	void bind();
	void unbind();
	unsigned int m_index_count;
	unsigned int m_vertex_count;



protected:
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int rows;
	unsigned int cols;

	std::vector<unsigned int>m_indices;
	std::vector<Vertex> m_vertices;


};


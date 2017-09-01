#pragma once
#include "Geo.h"
#include <vector>
#include <glm\glm.hpp>


class Mesh
{
public:
	Mesh();
	~Mesh();


	void create_buffers();
	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);

	void bind();
	void unbind();
	unsigned int index_count;
	unsigned int vertex_count;



protected:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;

	std::vector<unsigned int>m_indices;
	std::vector<Vertex> m_vertices;


};


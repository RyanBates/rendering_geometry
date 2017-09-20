#include "Mesh.h"
#include "Shader.h"
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
using namespace std;

Mesh::Mesh()//: m_VAO(0), m_VBO(0), m_IBO(0), m_index_count(0), m_vertex_count(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::create_buffers()
{
	//generates the vertex array object
	glGenVertexArrays(1, &m_VAO);
	//binds the vertex array
	glBindVertexArray(m_VAO);
	//generates the Vertex and Index Buffer Objects.
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	//generates the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	
	
	
	//generates the Index Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count *sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::initialize(vector<Vertex>& verts, vector<unsigned int>& indices)
{
	for (auto v : verts)
	{
		m_vertices.push_back(v);
	}
	m_vertex_count = m_vertices.size();
	for (auto i : indices)
	{
		m_indices.push_back(i);
	}
	m_index_count = m_indices.size();

	create_buffers();
}

void Mesh::bind()
{
	glBindVertexArray(m_VAO);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

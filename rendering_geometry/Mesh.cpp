#include "Mesh.h"
#include "Shader.h"
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
using namespace std;

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::create_buffers()
{
	
	//generates Buffer Objects.
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	
	//generates the vertex array object
	glGenVertexArrays(1, &m_VAO);

	//binds the vertex array
	glBindVertexArray(m_VAO);

	//sets the Vertex Buffer data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);
	
	//sets the Index Buffer data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count *sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	//normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) * 2));

	//Uv
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4) * 3));
	
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

}

void Mesh::bind()
{
	glBindVertexArray(m_VAO);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

#include "Mesh.h"
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
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	//generates the Vertex Buffer Object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), &m_vertices, GL_STATIC_DRAW);

	//generates the Index Buffer Object
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), &m_indices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	delete[] &m_vertices;
	delete[] &m_indices;
}

void Mesh::initialize(vector<Vertex>& verts, vector<unsigned int>& indices)
{



}

void Mesh::bind()
{
	glBindVertexArray(this->m_VAO);
}

void Mesh::unbind()
{
	glBindVertexArray(0);
}

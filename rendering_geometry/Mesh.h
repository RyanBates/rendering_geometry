#pragma once
#include "Geo.h"
#include <vector>
#include <glm\glm.hpp>

struct Vertex {

	vec4 position;
	vec4 Colour;
	vec4 normal;
	vec4 tangent;
	vec4 bitangent;
	vec2 texcoord;
};

struct Lighting{
	vec3 diffuse;
	float specular;
	vec3 dir;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

 
class Mesh
{
public:
	Mesh();
	~Mesh();

	void initialize(std::vector<Vertex>&verts, std::vector<unsigned int>&indices);
	void create_buffers();

	void bind();
	void unbind();
	unsigned int m_index_count;
	unsigned int m_vertex_count;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

protected:
	std::vector<unsigned int>m_indices;
	std::vector<Vertex> m_vertices;


};
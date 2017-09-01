#pragma once
class Mesh
{
public:
	Mesh();
	~Mesh();


	void create_buffers();
	void initialize(vector<Vertex>&verts, vector<unsigned int>&indices);

	void bind();
	void unbind();
	unsigned int index_count;
	unsigned int vertex_count;



protected:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ibo;



private:
	vector<unsigned int>m_indices;
	vector<Vertex> m_vertices;


};


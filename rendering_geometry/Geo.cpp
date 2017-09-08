#include "Geo.h"
#include "gl_core_4_4.h"
#include <stdio.h>
#include <assert.h>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <vector>
#include "Shader.h"

float PI = 3.14159265359;


Geo::Geo()
{
}
Geo::~Geo()
{
}

void Geo::generateGrid(unsigned int rows, unsigned int cols)
{
	//this is what gives the color to the objects.
	Vertex* aoVertices = new Vertex[rows * cols];

	for (unsigned int r = 0; r < rows; ++r)
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].Position = vec4((float)c, 0, (float)r, 1);
			// create some arbitrary colour based off something
			// that might not be related to tiling a texture
			vec3 colour = vec3(sinf((c / (float)(cols - 1))* (r / (float)(rows - 1))));
			aoVertices[r * cols + c].Color = vec4(colour, 1);
		}

	//this is what will give the points to the trangles.
	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];

	unsigned int index = 0;
	for (unsigned int r = 0; r<(rows - 1); ++r)
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//tri 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			//tri2
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1)* cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}

	//generates the Vertex Buffer Object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//generates the Index Buffer Object
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);


	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	//code to bind VBO & IBO.
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glBindBuffer(m_VBO, m_IBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete[] aoVertices;
	delete[] auiIndices;
}

void Geo::startup()
{

	Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) };//bl	
	Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//br
	Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//tl
	Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) };//tr
	Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) };//tr	

	std::vector<Vertex> vertices{ a,b,c,d,e };
	std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };


}

vector<vec4> Geo::GenHalfCircle(int r = 2, int np = 3)
{
	vector<vec4> half = vector<vec4>(np);

 	float angle = PI / (np - 1);

	for (int i = 0; i < np; i++)
	{
		half[i].x = sin(angle) * r;
		half[i].y = cos(angle) * r;
		half[i].z = 0.f;
		half[i].w = 1.f;
	}

	return half;
}

vector<vec4> Geo::GenSphere(vector<vec4> np, int nm = 4)
{
	vector<vec4> sphere;

	for (int i = 0; i < nm; ++i)
	{
		float slice = (2 * PI) / nm - 1;
		float phi = i / slice;

		for (int j = 0; j < np.size; ++j)
		{
			float newX = np[j].x * sin(phi);
			float newY = np[j].y * cos(phi);
			float newZ = np[j].z;
						
			sphere.push_back(vec4(newX, newY, newZ, 1.f));
		}

	}

	return sphere;
}


void Geo::draw()
{
	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Begin("nope");
	ImGui::End();

	glUseProgram(m_programID);

	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");

	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionViewUniform));

	glBindVertexArray(m_VAO); 

	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;

	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
	
	/// draw triangle






	/// draw square






	/// draw half circle
	//glBindVertexArray(m_VAO);



	//glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);



	//glBindVertexArray(0);



	//glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLE_STRIP);

	/// draw sphere

	





}



void Geo::update(float)
{
	
}



void Geo::shutdown()
{
}
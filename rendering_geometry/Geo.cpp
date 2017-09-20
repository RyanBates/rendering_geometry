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
#include "Mesh.h"

float PI = 3.14159265359;


Geo::Geo() : TheShader(*m_shader), m_mesh(0)
{
	m_mesh = new Mesh();
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


	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);

		
	delete[] aoVertices;
	delete[] auiIndices;
}

vector<vec4> generateHalfCircle(int r, int np)
{
	vector<vec4> half = vector<vec4>(np);

	for (float i = 0; i < np; i++)
	{
		float angle = PI / (np - 1);

		float theta = angle* i;


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
		float slice = (2 * PI) / nm - 1;
		float phi = i / slice;

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
		rotate.push_back(0xFFFF);
	}

	return rotate;
}

void Geo::startup()
{

	auto eye = vec3(10, 10, 10);
	auto projection = perspective(quarter_pi<float>(), 16 / 9.f, .1f, 1000.f);
	auto view = glm::lookAt(eye, vec3(0), vec3(0, 1, 0));
	m_projectionViewUniform = view * projection;


	//loading from the shader class
	m_shader = new Shader();
	m_mesh = new Mesh();
	m_shader->defaultLoad();
	m_shader->attach();


	//this is to populate 
	vector<Vertex> ver;
	vector<unsigned int> uints;
	
	////matthew's vetices and indices
	//Vertex a = { glm::vec4(-5,  0, 0, 1)		, glm::vec4(.1, .1, .1, 1) };//bl
	//Vertex b = { glm::vec4(5,  0, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//br
	//Vertex c = { glm::vec4(5, -5, 0, 1)			, glm::vec4(.1, .1, .1, 1) };//tl
	//Vertex d = { glm::vec4(-5, -5, 0, 1)		, glm::vec4(1, 0, 0, 1) };//tr
	//Vertex e = { glm::vec4(-5,  5, 0, 1)		, glm::vec4(0, 0, 1, 1) };//tr

	//std::vector<Vertex> vertices{ a,b,c,d,e };
	//std::vector<unsigned int> indices{ 0, 1, 2, 0, 2, 3, 0, 4, 1 };

	//rows = 3;
	//cols = rows;
	//generateGrid(rows, cols);


	/// indinces for plane




	/// indinces for cube




	/// indinces for sphere
	int r = 10;
	int np = r;
	int nm = 4;

	vector<vec4>halfcircle  =  generateHalfCircle(r, np); 

	vector<vec4>sphere = genSphere(halfcircle, nm);

	uints = sphereIndinces(nm, 3);
	
	for (auto p : sphere)
	{
		Vertex vert = { p, glm::vec4(.75, 0, .75, 1) };
		ver.push_back(vert);
	}
	
	m_mesh->initialize(ver, uints);
	
}

void Geo::draw()
{
	ImGui_ImplGlfwGL3_NewFrame();
	ImGui::Begin("nope");
	ImGui::End();


	m_shader->bind();

	unsigned int projectionViewUniform = m_shader->getUniform("mvp");

	m_mesh->bind();

	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_projectionViewUniform));

	

	glDrawElements(GL_TRIANGLES, m_mesh->m_index_count, GL_UNSIGNED_INT, 0);

	m_mesh->unbind();

	m_shader->unbind();	

	/// draw triangle




	/// draw square






	/// draw half circle



	


	/// draw sphere

	





}

void Geo::update(float)
{
	
}



void Geo::shutdown()
{
}
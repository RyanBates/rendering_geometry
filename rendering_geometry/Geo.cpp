#include "Geo.h"
#include "gl_core_4_4.h"
#include <glfw\include\GLFW\glfw3.h>
#include <stdio.h>
#include <assert.h>
#include <glm\ext.hpp>
#include <glm\fwd.hpp>
#include <glm\glm.hpp>

using namespace glm;


IN vec4 pos;
IN vec4 colour;

OUT vec4 vColour;

mat4 projectionViewWorldMatrix;

float times;
float heightScale;

Geo::Geo()
{
}


Geo::~Geo()
{
}


struct Vertex
{
	vec4 Position;
	vec4 Color;
};


void Geo::generateGrid(unsigned int rows, unsigned int cols)
{
	//this is what gives the color to the objects.
	Vertex* aoVertices = new Vertex[rows * cols];

	for (unsigned int r = 0; r < rows; ++r)
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r*cols + c].Position = vec4((float)c, 0, (float)r, 1);
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
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(vec4)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//generates the Index Buffer Object
	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	//code to bind VBO & IBO.
	glBindBuffer(m_VBO, m_IBO);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete[] aoVertices;
	delete[] auiIndices;
}

void Geo::startup()
{
	const char* vsSource = "#version410\n \
							layout(location=0) in vec4 Pos; \
							layout(location=1) in vec4 Color; \
							out vec4 vColor; \
							uniform mat4 projectionViewWorldMatrix; \
							void main(){vColor = Color; gl_Position = projectionViewWorldMatrix * Pos;}";

	const char* fsSource = "#version 410\n \
							in vec4 vColor; \
							out vec4 fragColor; \
							void main(){fragColor = vColor;}";

	int success = GL_FALSE;

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();

	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error: failed to link shader program! \n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	generateGrid(10, 10);
}

void Geo::shutdown()
{
}

void Geo::update(float)
{
}

void Geo::draw()
{
	glUseProgram(m_programID);
	unsigned int projectionViewUniform = glGetUniformLocation(m_programID, "projectionViewWorldMatrix");
	glUniformMatrix4fv(projectionViewUniform, 1, false, m_projectionViewUniform);

	glBindVertexArray(m_VAO);

	unsigned int indexCount = (rows - 1) * (cols - 1) * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Geo::run()
{
}


void Geo::main()
{

	vColour = colour;
	vec4 P = pos;
	P.y += sin(times + pos.x) * heightScale;

}

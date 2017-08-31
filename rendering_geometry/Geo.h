#pragma once

class Geo
{
public:
	Geo();
	~Geo();

	void generateGrid(unsigned int rows, unsigned int cols);
	virtual void startup();
	virtual void shutdown();
	virtual void update(float);
	virtual void draw();

	void run();
	void main();


	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_programID;

	unsigned int rows;
	unsigned int cols;

	const float* m_projectionViewUniform;

};


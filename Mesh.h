#pragma once


class Mesh
{
public:
	Mesh(float* vertices, int vertSize);
	Mesh(float* vertices, int vertSize, unsigned int* indices, int indiSize);
	~Mesh();

	void render();
private:
	unsigned int vaoId, vboId, eboId;

	int type;

	int vertSize;
	float* vertices;

	int indiSize;
	unsigned int* indices;
};


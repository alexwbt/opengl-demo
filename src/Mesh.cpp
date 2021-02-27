#include "Mesh.h"

#include <glad/glad.h>


Mesh::Mesh(float* vertices, int vertSize)
{
	type = 1;
	this->vertices = vertices;
	this->vertSize = vertSize;

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(vaoId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
}

Mesh::Mesh(float* vertices, int vertSize, unsigned int* indices, int indiSize)
{
	type = 2;
	this->vertices = vertices;
	this->vertSize = vertSize;
	this->indices = indices;
	this->indiSize = indiSize;

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);
	glGenBuffers(1, &eboId);
	
	glBindVertexArray(vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiSize * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vboId);

	if (type == 2)
	{
		glDeleteBuffers(1, &eboId);
		delete[] indices;
	}

	// delete[] vertices;
}

void Mesh::render()
{
	glBindVertexArray(vaoId);
	switch (type)
	{
	case 1:
		glDrawArrays(GL_TRIANGLES, 0, vertSize);
		break;
	case 2:
		glDrawElements(GL_TRIANGLES, indiSize, GL_UNSIGNED_INT, 0);
	}
}
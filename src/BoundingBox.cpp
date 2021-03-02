#include "pch.h"

const std::vector<float> cube_vertices = {
    // front
    -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
    // back
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
     1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f
};

const std::vector<uint32_t> cube_indices {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3
};


BoundingBox::BoundingBox(float x, float y, float z, float scale, Shader* shader)
	: GameObject(shader)
{
    setMesh(new Mesh(cube_vertices, cube_indices));
}

void BoundingBox::render(Camera* camera, glm::mat4 pv)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	GameObject::render(camera, pv);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

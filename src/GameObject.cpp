#include "pch.h"

GameObject::GameObject(Mesh* mesh, Shader* shader)
{
	this->mesh = mesh;
	position = glm::vec3(0);
	this->shader = shader;
}

GameObject::GameObject(Shader* shader)
{
	this->mesh = nullptr;
	position = glm::vec3(0);
	this->shader = shader;
}

GameObject::~GameObject()
{
	if (mesh)
	{
		delete mesh;
	}
}

void GameObject::setMesh(Mesh* mesh)
{
	if (this->mesh)
	{
		delete this->mesh;
	}
	this->mesh = mesh;
}

void GameObject::update(float deltaTime)
{

}

void GameObject::render(Camera* camera, glm::mat4 pv)
{
	if (mesh)
	{
		shader->use();

		Light::update(shader);
		shader->setVec3("cameraPos", camera->position);

		shader->setInt("diffuseMap", 0);
		shader->setFloat("specular", 0.2f);
		shader->setFloat("shininess", 16.0f);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position);

		shader->setMat4("mvp", pv * model);
		shader->setMat4("model", model);

		mesh->Render();
	}
}

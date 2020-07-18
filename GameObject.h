#pragma once

#include <glm.hpp>


class Camera;
class Shader;
class Mesh;

class GameObject
{
public:
	glm::vec3 position;

	GameObject(Mesh* mesh, Shader* shader);
	GameObject(Shader* shader);
	~GameObject();

	void setMesh(Mesh* mesh);

	void update(float deltaTime);
	virtual void render(Camera* camera, glm::mat4 pv);
private:
	Shader* shader;
	Mesh* mesh;
};

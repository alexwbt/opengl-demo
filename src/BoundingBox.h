#pragma once

class BoundingBox : public GameObject
{
public:
	BoundingBox(float x, float y, float z, float scale, Shader* shader);

	void render(Camera* camera, glm::mat4 pv) override;
};

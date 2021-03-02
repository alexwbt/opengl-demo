#pragma once

class Input
{
public:
	static void keyInput(float deltaTime);
	static void mouseInput(GLFWwindow* window, double x, double y);
	static void mouseWheelInput(GLFWwindow* window, double x, double y);

	static void setCamera(Camera* camera, float speed, float mouseSens);
private:
	static Camera* camera;
	static float cameraSpeed, mouseSens;

	static glm::vec2 mouse;
};


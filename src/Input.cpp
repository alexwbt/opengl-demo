#include "Input.h"
#include "Camera.h"
#include "Window.h"

#include <GLFW/glfw3.h>


Camera* Input::camera;
float Input::cameraSpeed, Input::mouseSens;
glm::vec2 Input::mouse = glm::vec2(-1);

void Input::keyInput(float deltaTime)
{
	if (glfwGetKey(Window::window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position += deltaTime * cameraSpeed * camera->front;
	if (glfwGetKey(Window::window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position -= deltaTime * cameraSpeed * camera->front;
	if (glfwGetKey(Window::window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position += deltaTime * cameraSpeed * camera->right;
	if (glfwGetKey(Window::window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position -= deltaTime * cameraSpeed * camera->right;
	if (glfwGetKey(Window::window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->position += deltaTime * cameraSpeed * glm::vec3(0, 1, 0);
	if (glfwGetKey(Window::window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->position -= deltaTime * cameraSpeed * glm::vec3(0, 1, 0);
}

void Input::mouseInput(GLFWwindow* window, double x, double y)
{
	if (mouse.x == -1 && mouse.y == -1)
	{
		mouse = glm::vec2(x, y);
	}

	camera->yaw += (x - mouse.x) * mouseSens;
	camera->pitch += (mouse.y - y) * mouseSens;
	mouse = glm::vec2(x, y);

	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;
}

void Input::mouseWheelInput(GLFWwindow* window, double x, double y)
{

}


void Input::setCamera(Camera* camera, float speed, float mouseSens)
{
	Input::camera = camera;
	cameraSpeed = speed;
	Input::mouseSens = mouseSens;
}

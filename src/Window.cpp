#include "pch.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Window::Window(const char* title, int width, int height)
	: width_(width), height_(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window_ = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window_)
	{
		glfwTerminate();
		throw std::runtime_error("Failed to create glfw window.");
	}

	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, FramebufferSizeCallback);
}

void Window::GetSize()
{
	glfwGetWindowSize(window_, &width_, &height_);
}

int Window::width() const
{
	return width_;
}

int Window::height() const
{
	return height_;
}

GLFWwindow* Window::window() const
{
	return window_;
}

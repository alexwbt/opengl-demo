#pragma once

class Window final
{
public:
	Window(const char* title, int width, int height);

	void GetSize();

	int width() const;
	int height() const;
	GLFWwindow* window() const;

private:
	GLFWwindow* window_;
	int width_, height_;
};


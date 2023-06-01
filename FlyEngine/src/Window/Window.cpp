#include "Window.h"
#include <string>

Window::Window(int width, int height, std::string title)
{
	windowWidth = width;
	windowHeight = height;
	windowTitle = title;
	//if(GL)
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
}

Window::~Window()
{
	
}

void Window::Resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

std::string Window::GetWindowName()
{
	return windowTitle;
}

glm::vec2 Window::GetWindowSize()
{
	return glm::vec2(windowWidth,windowHeight);
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

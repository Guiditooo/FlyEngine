#include "Window.h"
#include <string>

int Window::windowCount = 0;

Window::Window(int width, int height, std::string title)
{
	windowWidth = width;
	windowHeight = height;
	windowTitle = title;
	//if(GL)
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	
	windowCount++;
}

Window::~Window()
{
	windowCount--;
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

int Window::GetWindowCount()
{
	return windowCount;
}


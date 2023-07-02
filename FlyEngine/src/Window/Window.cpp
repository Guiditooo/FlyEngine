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

Window::Window(std::string title)
{
	windowWidth = INITIAL_WIDTH;
	windowHeight = INITIAL_HEIGHT;
	windowTitle = title;
	//if(GL)
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);

	windowCount++;
}

Window::~Window()
{
	windowCount--;
}

void Window::Resize(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	windowHeight = newHeight;
	windowWidth = newWidth;
}

void Window::Resize(glm::vec2 newDim)
{
	glViewport(0, 0, newDim.y, newDim.x);
	windowHeight = newDim.y;
	windowWidth = newDim.x;
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


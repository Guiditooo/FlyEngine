#include "Window.h"
#include <string>

namespace FlyEngine
{

	const int INITIAL_HEIGHT = 720;
	const int INITIAL_WIDTH = 1080;
	int Window::windowCount = 0;

	Window::Window(int width, int height, std::string title)
	{
		windowWidth = width;
		windowHeight = height;
		windowTitle = title;

		CreateWindow();
	}

	Window::Window(std::string title)
	{
		windowWidth = INITIAL_WIDTH;
		windowHeight = INITIAL_HEIGHT;
		windowTitle = title;
		
		CreateWindow();
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
		return glm::vec2(windowWidth, windowHeight);
	}

	GLFWwindow* Window::GetWindow()
	{
		return window;
	}

	void Window::CreateWindow()
	{
		if (!glfwInit())
		{
			std::cout << "GLFW not initialized!" << std::endl;
			exit(EXIT_FAILURE);
		}
		const char* auxName = windowTitle.c_str();
		window = glfwCreateWindow(windowWidth, windowHeight, auxName, NULL, NULL);
		//window = glfwCreateWindow(10, 10, "Hola", NULL, NULL);

		if (!window)
		{
			std::cout << "Error on WINDOW initialization" << std::endl;
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		windowCount++;
	}

	int Window::GetWindowCount()
	{
		return windowCount;
	}

}
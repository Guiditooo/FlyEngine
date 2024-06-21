#ifndef WINDOW_H
#define WINDOW_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>

namespace FlyEngine
{
	class Window
	{
	private:
		GLFWwindow* window;
		int windowWidth;
		int windowHeight;
		std::string windowTitle;
		bool shouldClose;

		static int windowCount;
		void CreateWindow();

	public:
		Window(int width, int height, std::string title);
		Window(std::string title);
		~Window();

		void Resize(int newWidth, int newHeight);
		void Resize(glm::vec2 newDim);

		std::string GetWindowName();
		glm::vec2 GetWindowSize();
		GLFWwindow* GetWindow();

		static int GetWindowCount();

	};

}

#endif // !
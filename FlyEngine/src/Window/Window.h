#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>

class Window
{
private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
	std::string windowTitle;
	bool shouldClose;

	static int windowCount;

	const int INITIAL_HEIGHT = 720;
	const int INITIAL_WIDTH = 1080;

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

#endif // !

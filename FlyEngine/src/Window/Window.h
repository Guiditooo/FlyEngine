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

public:
	Window(int width, int height, std::string title);
	~Window();

	void Resize(int width, int height);

	std::string GetWindowName();
	glm::vec2 GetWindowSize();
	GLFWwindow* GetWindow();




};

#endif // !

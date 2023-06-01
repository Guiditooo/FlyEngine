#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* window;
	int windowWidth;
	int windowHeight;
	std::string windowTitle;

public:
	Window();
	~Window();
	void Resize(int width, int height);
};

#endif // !

#ifndef INPUT_H
#define INPUT_H

#include <FlyFunctions/KeyCode/KeyCode.h>
#include <GLFW/glfw3.h>

static class FLY_API Input
{
private:

public:
	static bool GetKeyUp(GLFWwindow* window, FLY_ENGINE::KeyCode key);
	static bool GetKeyPressed(GLFWwindow* window, FLY_ENGINE::KeyCode key);
	static bool GetKeyDown(GLFWwindow* window, FLY_ENGINE::KeyCode key);
};

#endif // !
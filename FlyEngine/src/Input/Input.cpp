#include "Input.h"

bool Input::GetKeyUp(GLFWwindow* window, FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_RELEASE;
}

bool Input::GetKeyPressed(GLFWwindow* window, FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_REPEAT;
}

bool Input::GetKeyDown(GLFWwindow* window, FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
}

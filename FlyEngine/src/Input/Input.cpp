#include "Input.h"

Window* Input::window = nullptr;

void Input::SetContextWindow(Window* newWindow)
{
	window = newWindow;
}

bool Input::GetKeyUp(FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_RELEASE;
}

bool Input::GetKeyPressed(FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_REPEAT;
}

bool Input::GetKeyDown(FLY_ENGINE::KeyCode key)
{
	return glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS;
}

#include "Input.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include <string>

namespace FlyEngine
{
	namespace Utils
	{

		Window* Input::window = nullptr;

		void Input::SetContextWindow(Window* newWindow)
		{
			window = newWindow;
		}

		bool Input::GetKeyUp(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_RELEASE)
			{
				Debugger::ConsoleMessage("Tecla soltada!", 2, 0, 1);
				return true;
			}
			return false;
		}

		bool Input::GetKeyPressed(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_REPEAT)
			{
				Debugger::ConsoleMessage("Tecla Presionada!", 2, 0, 1);
				return true;
			}
			return false;
		}

		bool Input::GetKeyDown(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS)
			{
				Debugger::ConsoleMessage("Tecla Mantenida Presionada!", 2, 0, 1);
				return true;
			}
			return false;
		}

	}

}
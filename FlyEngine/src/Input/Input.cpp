#include "Input.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include <string>

namespace FlyEngine
{
	namespace Utils
	{

		Window* Input::window = nullptr;

		//std::unordered_set<KeyCode> Input::pressedKeys;

		void Input::SetContextWindow(Window* newWindow)
		{
			window = newWindow;
		}
		/*
		bool Input::GetKeyUp(KeyCode key)
		{
			if (pressedKeys.empty() || pressedKeys.count(key) != 1) return false;

			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_RELEASE)
			{
				Debugger::ConsoleMessageID("Tecla soltada!", 2, 0, 1);
				pressedKeys.erase(key);
				return true;
			}
			return false;
		}
		bool Input::GetKeyPressed(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_REPEAT)
			{
				Debugger::ConsoleMessageID("Tecla Presionada!", 2, 0, 1);
				pressedKeys.insert(key);
				return true;
			}
			return false;
		}
		*/
		bool Input::GetKeyDown(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS)
			{
				Debugger::ConsoleMessageID("Tecla Mantenida!", 2, 0, 1);
				//pressedKeys.insert(key);
				return true;
			}
			return false;
		}
		/*
		void Input::GlfwTester(KeyCode key)
		{
			switch (glfwGetKey(window->GetWindow(), static_cast<int>(key)))
			{
			case GLFW_PRESS:
				Debugger::ConsoleMessage("PRESS!", 2, 0, 1);
				break;
			case GLFW_REPEAT:
				Debugger::ConsoleMessage("REPEAT!", 2, 0, 1);
				break;
			case GLFW_RELEASE:
				Debugger::ConsoleMessage("RELEASE!", 2, 0, 1);
				break;
			default:
				Debugger::ConsoleMessage("UNKNOWN!", 2, 0, 1);
				break;
			}
		}
		*/
	}

}
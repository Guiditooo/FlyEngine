#include "Input.h"

#include <string>

#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	namespace Utils
	{

		bool Input::currentKeys[GLFW_KEY_LAST + 1] = { false };
		bool Input::previousKeys[GLFW_KEY_LAST + 1] = { false };
		bool Input::activeMessages = true;

		FlyEngine::Window* Input::window = nullptr;


		void Input::SetContextWindow(Window* win)
		{
			window = win;
			glfwSetKeyCallback(window->GetWindow(), KeyCallback);
		}

		void Input::Update()
		{
			for (int i = 0; i <= GLFW_KEY_LAST; ++i)
			{
				previousKeys[i] = currentKeys[i];
			}
		}

		bool Input::GetKeyDown(KeyCode key)
		{
			return currentKeys[static_cast<int>(key)] && !previousKeys[static_cast<int>(key)];
		}

		bool Input::GetKeyPressed(KeyCode key)
		{
			return currentKeys[static_cast<int>(key)];
		}

		bool Input::GetKeyUp(KeyCode key)
		{
			return !currentKeys[static_cast<int>(key)] && previousKeys[static_cast<int>(key)];
		}

		INPUT_STATE Input::GetKeyState(KeyCode key)
		{
			INPUT_STATE state = INPUT_STATE::NONE;
			/*
			if (currentKeys[static_cast<int>(key)] && !previousKeys[static_cast<int>(key)])
			{
				state = INPUT_STATE::DOWN;
				if (activeMessages)
					Debugger::ConsoleMessage("Key Down!", 1, 0, 1, 1);
			}
			else if (currentKeys[static_cast<int>(key)] && previousKeys[static_cast<int>(key)])
			{
				state = INPUT_STATE::PRESSED;
				if (activeMessages)
					Debugger::ConsoleMessage("Key Pressed!");
			}
			else if (!currentKeys[static_cast<int>(key)] && previousKeys[static_cast<int>(key)])
			{
				state = INPUT_STATE::RELEASED;
				if (activeMessages)
					Debugger::ConsoleMessage("Key Released!", 1, 0, 1, 1);
			}
			else
			{
				state = INPUT_STATE::NONE;
				if (activeMessages)
					Debugger::ConsoleMessage("No pressing Key!");
			}
			*/
			return state;
		}

		void Input::ToggleMessages()
		{
			activeMessages = !activeMessages;
		}

		void FlyEngine::Utils::Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key < 0 || key > GLFW_KEY_LAST) return;

			if (action == GLFW_PRESS)
			{
				currentKeys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				currentKeys[key] = false;
			}
		}

	}

}
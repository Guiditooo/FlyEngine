#include "Input.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include "Window/Window.h"

#include <string>
#include <functional>

namespace FlyEngine
{
	namespace Utils
	{

		const float MOUSE_SENSIBILITY = 0.1f;

		//std::unordered_set<KeyCode> Input::pressedKeys;

		Input::Input()
		{
			window = nullptr;
			moveX = 0;
			moveY = 0;
		}

		Input::Input(Window* newWindow)
		{
			window = newWindow;
			moveX = 0;
			moveY = 0;
		}

		void Input::SetContextWindow(Window* newWindow)
		{
			window = newWindow;
		}
		
		//void Input::SetUp(Window* newWindow)
		//{
		//	SetContextWindow(newWindow);
		//	/*
		//	glfwSetCursorPosCallback(newWindow->GetWindow(), [](GLFWwindow* window, double mouseX, double mouseY)
		//		{
		//			static float lastX = 0.0f;
		//			static float lastY = 0.0f;
		//			static bool firstMove = true;

		//			if (firstMove)
		//			{
		//				lastX = mouseX;
		//				lastY = mouseY;
		//				firstMove = false;
		//			}

		//			moveX = mouseX - lastX;
		//			moveY = lastY - mouseY; // Invierte el desplazamiento del ratón para que la cámara no se invierta
		//			lastX = mouseX;
		//			lastY = mouseY;

		//			moveX *= MOUSE_SENSIBILITY;
		//			moveY *= MOUSE_SENSIBILITY;

		//		}
		//	);
		//	*/
		//}
	

#pragma region CHECK LATER

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

#pragma endregion

		bool Input::GetKeyDown(KeyCode key)
		{
			if (glfwGetKey(window->GetWindow(), static_cast<int>(key)) == GLFW_PRESS)
			{
				//Debugger::ConsoleMessageID("Tecla Mantenida!", 2, 0, 1);
				//pressedKeys.insert(key);
				return true;
			}
			return false;
		}

		glm::vec2 Input::GetMousePosition()
		{
			glm::vec2 mousePosition;
			double xpos, ypos;

			glfwGetCursorPos(window->GetWindow(), &xpos, &ypos);

			mousePosition.x = xpos;
			mousePosition.y = ypos;

			return mousePosition;
		}

		/*
		void Input::OnMouseMovementCallback(std::function<void(float, float)> callback, float& xMovement, float& yMovement)
		{
			xMovement = moveX;
			yMovement = moveY;

			callback(xMovement, yMovement);
		}
		*/

	}

}
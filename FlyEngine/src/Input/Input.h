#ifndef INPUT_H
#define INPUT_H

#include <FlyFunctions/KeyCode/KeyCode.h>
#include <glm/glm.hpp>
#include <unordered_set>

#include "Window/Window.h"

namespace FlyEngine
{

	namespace Utils
	{

		enum class FLY_API INPUT_STATE
		{
			DOWN,
			PRESSED,
			RELEASED,
			NONE
		};

		class FLY_API Input
		{
		private:
			static Window* window; 
			static bool currentKeys[GLFW_KEY_LAST + 1];
			static bool previousKeys[GLFW_KEY_LAST + 1];

			static bool activeMessages;

		public:
			static void SetContextWindow(Window* newWindow);

			static bool GetKeyUp(KeyCode key);
			static bool GetKeyPressed(KeyCode key);
			static bool GetKeyDown(KeyCode key);
			static INPUT_STATE GetKeyState(KeyCode key);

			static void Update();

			static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

			static void ToggleMessages();
		};

	}

}
#endif // !
#ifndef INPUT_H
#define INPUT_H

#include <FlyFunctions/KeyCode/KeyCode.h>
#include <glm/glm.hpp>
//#include <functional>
//#include <unordered_set>

namespace FlyEngine
{
	class Window;

	namespace Utils
	{

		class FLY_API Input
		{
		private:
			Window* window;
			float moveX;
			float moveY;
			//static std::unordered_set<KeyCode> pressedKeys;

		public:
			Input();
			Input(Window* newWindow);
			//void SetUp(Window* newWindow);
			void SetContextWindow(Window* newWindow);
			//static void GlfwTester(KeyCode key);

			//static bool GetKeyUp(KeyCode key);
			//static bool GetKeyPressed(KeyCode key);
			bool GetKeyDown(KeyCode key);

			glm::vec2 GetMousePosition();

			//static void OnMouseMovementCallback(std::function<void(float, float)> callback, float& xMovement, float& yMovement);

		};

	}

}
#endif // !
#ifndef INPUT_H
#define INPUT_H

#include <Window/Window.h>
#include <FlyFunctions/KeyCode/KeyCode.h>
//#include <unordered_set>

namespace FlyEngine
{

	namespace Utils
	{

		class FLY_API Input
		{
		private:
			static Window* window;
			//static std::unordered_set<KeyCode> pressedKeys;
		public:
			static void SetContextWindow(Window* newWindow);
			static void GlfwTester(KeyCode key);

			static bool GetKeyUp(KeyCode key);
			static bool GetKeyPressed(KeyCode key);
			static bool GetKeyDown(KeyCode key);
		};

	}

}
#endif // !
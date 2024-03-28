#ifndef INPUT_H
#define INPUT_H

#include <Window/Window.h>
#include <FlyFunctions/KeyCode/KeyCode.h>


namespace FlyEngine
{

	namespace Utils
	{

		class FLY_API Input //SI PONGO LA API, TIRA ERROR PREGUNTAR
		{
		private:
			static Window* window;
		public:
			static void SetContextWindow(Window* newWindow);

			static bool GetKeyUp(KeyCode key);
			static bool GetKeyPressed(KeyCode key);
			static bool GetKeyDown(KeyCode key);
		};

	}

}
#endif // !
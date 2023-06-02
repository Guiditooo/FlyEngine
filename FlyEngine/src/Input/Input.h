#ifndef INPUT_H
#define INPUT_H

#include <Window/Window.h>
#include <FlyFunctions/KeyCode/KeyCode.h>

class /*FLY_API*/ Input //SI PONGO LA API, TIRA ERROR PREGUNTAR
{
private:
	static Window* window;
public:
	static void SetContextWindow(Window* newWindow);

	static bool GetKeyUp(FLY_ENGINE::KeyCode key);
	static bool GetKeyPressed(FLY_ENGINE::KeyCode key);
	static bool GetKeyDown(FLY_ENGINE::KeyCode key);
};

#endif // !
#ifndef BASEGAME_H
#define BASEGAME_H

#define FLY_EXPORTS

#include <GLFW/glfw3.h>
#include <Exports/Exports.h>
#include "Window/Window.h"


class BaseGame
{
private:
	static bool isRunning;
	static Window* window;

public:
	BaseGame();
	~BaseGame();

	static void RunGame();
	static bool IsGameRunning();


protected:
	static void Init();
	static void Update();
	static void Draw();
	static void Deinit();

};

#endif // !

#ifndef BASEGAME_H
#define BASEGAME_H

#define FLY_EXPORTS

#include <GLFW/glfw3.h>
#include <Exports/Exports.h>
#include "Window/Window.h"


class FLY_API BaseGame
{
private:
	static bool isRunning;
	Window* window;

public:
	BaseGame();
	~BaseGame();

	void RunGame();
	static bool IsGameRunning();

protected:
	void Init();
	void Update();
	void Draw();
	void Deinit();

};

#endif // !

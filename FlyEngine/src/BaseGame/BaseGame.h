#ifndef BASEGAME_H
#define BASEGAME_H

#include <GLFW/glfw3.h>

class BaseGame
{
private:
	static bool isRunning;

	void Init();
	void Update();
	void Draw();
	void Deinit();

public:
	BaseGame();
	~BaseGame();

	void RunGame();
	static bool IsGameRunning();
};

#endif // !

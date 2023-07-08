#ifndef BASEGAME_H
#define BASEGAME_H

#include <Exports/Exports.h>
#include <iostream>
/*
#include <FlyFunctions/ColorCode/ColorCode.h>
#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
#include <FlyFunctions/KeyCode/KeyCode.h>
#include <FlyFunctions/Color/Color.h>
#include <Rectangle/Rectangle.h>
#include <Material/Material.h>
#include <Triangle/Triangle.h>
#include <Camera/Camera.h>
#include <Input/Input.h>
#include <Line/Line.h>
*/
struct GLFWwindow;
class Window;

class FLY_API BaseGame
{
private:
	bool isRunning;
	bool checkEsc;
	Window* window;

	int initialWindowWidth;
	int initialWindowHeight;
	std::string initialWindowName;

	void SwapBuffers();

	void InternalInit();
	void InternalUpdate();
	void InternalDraw();
	void InternalDeinit();


public:
	BaseGame();
	~BaseGame();

	void RunGame();
	bool IsGameRunning();
	void SetWindowParameters(int width, int height, std::string name = "FlyEngine");

	void ToggleClosingWithEsc();

protected:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Deinit() = 0;

};

#endif // !

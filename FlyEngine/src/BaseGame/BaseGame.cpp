#include "BaseGame.h"
#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
#include <FlyFunctions/Color/Color.h>
#include <FlyFunctions/ColorCode/ColorCode.h>
#include <Input/Input.h>

bool BaseGame::isRunning = false;
Window* BaseGame::window = nullptr;

using namespace FLY_ENGINE;

BaseGame::BaseGame()
{
	isRunning = false;
}

BaseGame::~BaseGame()
{
}

void BaseGame::Init()
{
	Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
	Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
	std::cin.get();
	system("cls");

	glfwInit();
	window = new Window(800, 600, "Fly Engine");
	glfwMakeContextCurrent(window->GetWindow());

	Input::SetContextWindow(window);

}

void BaseGame::Update()
{
	if (Input::GetKeyDown(KeyCode::KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window->GetWindow(), true);
	}
}

void BaseGame::Draw()
{	
	glm::vec4 bgColor = Color::GetColor(COLOR::RAYWHITE);

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window->GetWindow());
}

void BaseGame::Deinit()
{
	glfwTerminate();

	FLY_ENGINE::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
	FLY_ENGINE::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
	std::cin.get();
	system("cls");

	delete window;
}

void BaseGame::RunGame()
{
	isRunning = true;

	Init();
	
	while (isRunning && !glfwWindowShouldClose(window->GetWindow()))
	{
		Update();
		Draw();
		glfwPollEvents();
	}

	Deinit();
}

bool BaseGame::IsGameRunning()
{
	return isRunning;
}


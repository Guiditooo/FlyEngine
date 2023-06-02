#include "BaseGame.h"
#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
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
	//std::cout << std::endl << "Start of update code" << std::endl;
	
	if (Input::GetKeyDown(KeyCode::KEY_ESCAPE))
		glfwSetWindowShouldClose(window->GetWindow(), true);

	//std::cout << std::endl << "End of update code" << std::endl;
}

void BaseGame::Draw()
{
	//std::cout << std::endl << "Start of draw code" << std::endl;

	glClearColor(0.1f, 0.4f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window->GetWindow());


	//std::cout << std::endl << "End of draw code" << std::endl;
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


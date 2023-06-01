#include "BaseGame.h"
#include <iostream>

bool BaseGame::isRunning = false;

BaseGame::BaseGame()
{
	window = new Window(800, 600, "Fly Engine");;
	isRunning = false;
}

BaseGame::~BaseGame()
{
}

void BaseGame::Init()
{
}

void BaseGame::Update()
{
	std::cout << std::endl << "Start of update code" << std::endl;
	
	std::cout << std::endl << "End of update code" << std::endl;
}

void BaseGame::Draw()
{
	std::cout << std::endl << "Start of draw code" << std::endl;

	std::cout << std::endl << "End of draw code" << std::endl;
}

void BaseGame::Deinit()
{
	std::cout << std::endl << "Start of draw code" << std::endl;

	std::cout << std::endl << "End of draw code" << std::endl;
}

void BaseGame::RunGame()
{
	isRunning = true;
	Init();
	while (isRunning)
	{
		Draw();
		Update();
	}
	Deinit();
}

bool BaseGame::IsGameRunning()
{
	return isRunning;
}

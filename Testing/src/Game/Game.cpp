#include "Game.h"
#include <time.h>

namespace FlyGame
{
	using namespace std;

	Game::Game(int width, int height, string name)
	{
		winWidth = width;
		winHeight = height;
		gameName = name;
		SetWindowParameters(width, height, name);
	}

	Game::Game(int width, int height)
	{
		winWidth = width;
		winHeight = height;
		SetWindowParameters(width, height);
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		SetWindowParameters(winWidth, winHeight, gameName);
		rec = new FlyEngine::Entities::Rectangle();
		rec->SetColor(FlyEngine::Utils::COLOR::CYAN);
		aux = 0;
	}

	void Game::Update()
	{
		//FlyEngine::Utils::Input::GlfwTester(FlyEngine::Utils::KeyCode::KEY_X);

		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_E))
		{
			rec->Rotate(0, 0, 0.01f);
		}
		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_Q))
		{
			rec->Rotate(0, 0, -0.01f);
		}

		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_A))
		{
			rec->Rotate(0.01f, 0, 0);
		}
		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_D))
		{
			rec->Rotate(-0.01f, 0, 0);
		}

		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_W))
		{
			rec->Rotate(0, 0.01f, 0);
		}
		if (FlyEngine::Utils::Input::GetKeyDown(FlyEngine::Utils::KeyCode::KEY_S))
		{
			rec->Rotate(0, -0.01f, 0);
		}
		
	}

	void Game::Deinit()
	{

	}

}
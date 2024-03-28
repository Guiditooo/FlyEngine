#include "Game.h"

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
		SetWindowParameters(winWidth, winHeight, gameName);
		rec = new FlyEngine::Entities::Rectangle();
		rec->SetColor(FlyEngine::Utils::COLOR::CYAN);
		rec->Rotate(0, 0, 45);
		aux = 0;
	}

	void Game::Update()
	{
		if (FlyEngine::Utils::Input::GetKeyPressed(FlyEngine::Utils::KeyCode::KEY_E))
		{
			rec->Rotate(0, 0, 1);
		}
		if (FlyEngine::Utils::Input::GetKeyPressed(FlyEngine::Utils::KeyCode::KEY_Q))
		{
			rec->Rotate(0, 0, -1);
		}
	}

	void Game::Deinit()
	{

	}

}
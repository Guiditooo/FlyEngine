#include "Game.h"
#include <time.h>

namespace FlyGame
{
	using namespace std;

	Camera* mainCamera;

	Game::Game(int width, int height, string name)
	{
		SetWindowParameters(width, height, name);
		input = Utils::Input();
	}

	Game::Game(int width, int height)
	{
		SetWindowParameters(width, height, "%NaN");
	}

	Game::~Game()
	{

	}

	Camera* Game::GetMainCamera()
	{
		return mainCamera;
	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		mainCamera = new Camera(window);
		input = Utils::Input(window);

		//cube = new FlyEngine::Entities::Rectangle();
		cube = new FlyEngine::Entities::Cube();
		cube->SetColor(FlyEngine::Utils::COLOR::GREEN);
		//cube->SetRotation(0.5f, 0.5f, 0.5f);
		aux = 0;

		//ToggleClosingWithEsc();
	}

	void Game::Update()
	{
				
	}

	void Game::Deinit()
	{

	}


}
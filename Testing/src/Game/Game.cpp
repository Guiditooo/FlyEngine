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
		cameraController = new CameraController(window, 
			KeyCode::KEY_W, KeyCode::KEY_S, 
			KeyCode::KEY_SPACE, KeyCode::KEY_LEFT_SHIFT, 
			KeyCode::KEY_A, KeyCode::KEY_D
		);
		
		cube = new FlyEngine::Entities::Cube();
		cube->SetColor(FlyEngine::Utils::COLOR::GREEN);
		
		//Rectangle(1,2,3,4);
	}

	void Game::Update()
	{
		cameraController->Update();
	}

	void Game::Deinit()
	{

	}


}
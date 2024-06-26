#include <time.h>
#include <string>

#include "Game.h"

#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyGame
{
	using namespace std;

	bool movingPlayer = true;

	Game::Game(int width, int height, string name)
	{
		SetWindowParameters(width, height, name);

		cameraController = nullptr;

		input = nullptr;
		rec = nullptr;
		player = nullptr;
		piso = nullptr;
		cube = nullptr;
		light = nullptr;

		movingObject = MovingObject::Cube;
	}

	Game::Game(int width, int height)
	{
		SetWindowParameters(width, height, "%NaN");

		cameraController = nullptr;

		input = nullptr;
		rec = nullptr;
		player = nullptr;
		piso = nullptr;
		cube = nullptr;
		light = nullptr;

		movingObject = MovingObject::Cube;
	}

	Game::~Game()
	{
		if (rec != nullptr)
			delete rec;
		rec = nullptr;

		if (player != nullptr)
			delete player;
		player = nullptr;

		if (piso != nullptr)
			delete piso;
		piso = nullptr;

		if (cube != nullptr)
			delete cube;
		cube = nullptr;

		if (cameraController != nullptr)
			delete cameraController;
		cameraController = nullptr;
	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		mainCamera->SetPosition(-0.13f, 0.36f, -0.82f);

		cameraController = new CameraController(mainCamera, window,
			KeyCode::KEY_W, KeyCode::KEY_S,
			KeyCode::KEY_SPACE, KeyCode::KEY_LEFT_SHIFT,
			KeyCode::KEY_A, KeyCode::KEY_D
		);


		input = Utils::Input(window);
		//rec = CreateRectangle(0, 0, 1, 1000, 1000);
		piso = CreateRectangle(0, -1, 0, 1000, 1000);
		player = CreateCube(0, 0, 0, 100);
		cube = CreateCube(1, 0, 0, 100);
		light = CreateCube(0, 0, 0, 100);

		piso->SetName("Piso");
		player->SetName("Player");
		cube->SetName("Cubo Uno");
		light->SetName("Cubo Dos");

		piso->SetRotation(90, 0, 0);

		piso->SetColor(COLOR::BLUE);
		cube->SetColor(COLOR::CYAN);
		light->SetColor(COLOR::WHITE);
		player->SetColor(COLOR::YELLOW);

		piso->SetActive(true);
		player->SetActive(true);
		cube->SetActive(true);
		light->SetActive(true);

		SetLight(light);

	}

	void Game::Update()
	{
		
		Input inputSystem = Input(window);

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_ENTER))
		{
			int actualIndex = (int)movingObject;
			int nextIndex = actualIndex + 1;
			movingObject = (MovingObject)nextIndex;
			switch (movingObject)
			{
			case FlyGame::MovingObject::Camera:
				Debugger::ConsoleMessage("Moving Camera");
				break;
			case FlyGame::MovingObject::Light:
				Debugger::ConsoleMessage("Moving Light");
				break;
			case FlyGame::MovingObject::Cube:
			default:
				movingObject = MovingObject::Cube;
				Debugger::ConsoleMessage("Moving Player");
				break;
			}
		}
		switch (movingObject)
		{
		case FlyGame::MovingObject::Cube:
			MoveObject(cube, inputSystem, true);
			break;
		case FlyGame::MovingObject::Camera:
			cameraController->Update(false);
			break;
		case FlyGame::MovingObject::Light:
			MoveObject(light, inputSystem, false);
			break;
		default:
			break;
		}
	}

	void Game::Deinit()
	{

	}

	void Game::MoveObject(FlyEngine::Entities::Entity* entity, Input inputSystem, bool showMovement)
	{
		bool objectMoved = false;
		float sensibility = 1;
		float rotSensibility = 10;

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_W))
		{
			entity->MoveForward(sensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_S))
		{
			entity->MoveBackward(sensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_SPACE))
		{
			entity->MoveUp(sensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			entity->MoveDown(sensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_A))
		{
			entity->MoveLeft(sensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_D))
		{
			entity->MoveRight(sensibility);
			objectMoved = true;
		}

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_I))
		{
			entity->Rotate(rotSensibility, 0.0f, 0.0f);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_K))
		{
			entity->Rotate(-rotSensibility, 0.0f, 0.0f);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_J))
		{
			entity->Rotate(0.0f, rotSensibility, 0.0f);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_L))
		{
			entity->Rotate(0.0f, -rotSensibility, 0.0f);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_U))
		{
			entity->Rotate(0.0f, 0.0f, -rotSensibility);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_O))
		{
			entity->Rotate(0.0f, 0.0f, rotSensibility);
			objectMoved = true;
		}

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_KP_ADD))
		{
			float scaleSens = 1.01f;
			entity->Scale(scaleSens, scaleSens, scaleSens);
			objectMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_KP_SUBTRACT))
		{
			float scaleSens = 0.99f;
			entity->Scale(-scaleSens, -scaleSens, -scaleSens);
			objectMoved = true;
		}


		if (objectMoved && showMovement)
		{
			std::string text = "- Player Updated Position: (";
			text += std::to_string(entity->GetPosition().x);
			text += ",";
			text += std::to_string(entity->GetPosition().y);
			text += ",";
			text += std::to_string(entity->GetPosition().z);
			text += ")";
			Debugger::ConsoleMessage(&text[0], 1, 0, 1, 0);
		}
	}

}
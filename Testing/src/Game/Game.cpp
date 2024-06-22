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

		cameraController = new CameraController(mainCamera, window,
			KeyCode::KEY_W, KeyCode::KEY_S,
			KeyCode::KEY_SPACE, KeyCode::KEY_LEFT_SHIFT,
			KeyCode::KEY_A, KeyCode::KEY_D
		);

		input = Utils::Input(window);
		rec = CreateRectangle(0, 0, 1, 1000, 1000);
		piso = CreateRectangle(0, -1, 0, 1000, 1000);
		player = CreateRectangle(0, 0, 0, 80, 120);
		cube = CreateCube(0, 0, 0, 100);

		player->SetName("Player");
		piso->SetName("Piso");
		cube->SetName("Cubo");
		rec->SetName("Rectangulo");

		piso->SetRotation(90, 0, 0);

		piso->SetColor(COLOR::BLUE);
		player->SetColor(COLOR::YELLOW);
		cube->SetColor(COLOR::GREEN);

		rec->SetActive(false);
		piso->SetActive(true);
		player->SetActive(false);
		cube->SetActive(true);

	}

	void Game::Update()
	{
		Input inputSystem = Input(window);
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_ENTER))
		{
			movingPlayer = !movingPlayer;
			if (movingPlayer)
				Debugger::ConsoleMessage("Moving Player");
			else
				Debugger::ConsoleMessage("Moving Camera");
		}
		if (movingPlayer)
		{
			MoveObject(cube, inputSystem, true);
			//MoveObject(player, inputSystem, true);
		}
		else
		{
			cameraController->Update();
		}
	}

	void Game::Deinit()
	{

	}

	void Game::MoveObject(FlyEngine::Entities::Entity* entity, Input inputSystem, bool showMovement)
	{
		bool cameraMoved = false;
		float sensibility = 0.01f;

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_W))
		{
			entity->Translate(0.0f, 0.0f, sensibility);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_S))
		{
			entity->Translate(0.0f, 0.0f, -sensibility);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_SPACE))
		{
			entity->Translate(0.0f, sensibility, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			entity->Translate(0.0f, -sensibility, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_A))
		{
			entity->Translate(sensibility, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_D))
		{
			entity->Translate(-sensibility, 0.0f, 0.0f);
			cameraMoved = true;
		}

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_I))
		{
			entity->Rotate(-1, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_K))
		{
			entity->Rotate(1, 0.0f, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_J))
		{
			entity->Rotate(0.0f, -1, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_L))
		{
			entity->Rotate(0.0f, 1, 0.0f);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_U))
		{
			entity->Rotate(0.0f, 0.0f, -1);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_O))
		{
			entity->Rotate(0.0f, 0.0f, 1);
			cameraMoved = true;
		}

		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_KP_ADD))
		{
			float scaleSens = 1.01f;
			entity->Scale(scaleSens, scaleSens, scaleSens);
			cameraMoved = true;
		}
		if (inputSystem.GetKeyDown(Utils::KeyCode::KEY_KP_SUBTRACT))
		{
			float scaleSens = 0.99f;
			entity->Scale(-scaleSens, -scaleSens, -scaleSens);
			cameraMoved = true;
		}


		if (cameraMoved && showMovement)
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
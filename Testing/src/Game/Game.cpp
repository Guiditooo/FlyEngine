#include <time.h>
#include <string>

#include "Game.h"

#include "FlyFunctions/Debugger/Debugger.h"
#include "MaterialSpecification/MaterialSpecification.h"

namespace FlyGame
{
	using namespace std;

	bool movingPlayer = true;

	Game::Game(int width, int height, string name)
	{
		SetWindowParameters(width, height, name);

		cameraController = nullptr;

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

		rec = nullptr;
		player = nullptr;
		piso = nullptr;
		cube = nullptr;
		light = nullptr;

		texture = nullptr;

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

		if (light != nullptr)
			delete light;
		light = nullptr;

		if (cameraController != nullptr)
			delete cameraController;
		cameraController = nullptr;
	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		mainCamera->SetPosition(0.0f, 1.0f, 25.0f);
		//mainCamera->SetRotation(-90, 0, 0);

		cameraController = new CameraController(mainCamera, window);

		piso = CreateRectangle(0, 0, 0, 100000, 100000);
		player = CreateCube(0, 1, 0, 100);
		cube = CreateCube(2, 1, 0, 100);
		light = CreateCube(0, 3, 0, 100);

		texture = CreateTexture("res\\Textures\\Box.png");

		piso->SetName("Piso");
		player->SetName("Player");
		cube->SetName("Cubo Uno");
		light->SetName("Luz");

		piso->SetRotation(90, 0, 0);

		cube->GetMaterial()->GetSpecs()->SetSpecs(Materials::MaterialList::Emerald);
		piso->GetMaterial()->GetSpecs()->SetSpecs(Materials::MaterialList::Gold);
		light->GetMaterial()->GetSpecs()->SetSpecs(Materials::MaterialList::WhitePlastic);

		piso->SetColor(COLOR::WHITE);

		piso->SetActive(true);
		player->SetActive(true);
		cube->SetActive(true);
		light->SetActive(true);

		SetLight(light); //Cambiar cuando tenga la clase Light andando

	}

	void Game::Update()
	{

		if (Input::GetKeyPressed(KeyCode::KEY_KP_1))
		{
			movingObject = MovingObject::Cube;
			Debugger::ConsoleMessage("Moving Player");
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_2))
		{
			movingObject = MovingObject::Camera;
			Debugger::ConsoleMessage("Moving Camera");
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_3))
		{
			movingObject = MovingObject::Light;
			Debugger::ConsoleMessage("Moving Light");
		}

		switch (movingObject)
		{
		case FlyGame::MovingObject::Cube:
			MoveObject(cube, true);
			break;
		case FlyGame::MovingObject::Camera:
			cameraController->Update(true);
			break;
		case FlyGame::MovingObject::Light:
			MoveObject(light, true);
			break;
		default:
			break;
		}
	}

	void Game::Deinit()
	{

	}

	void Game::MoveObject(FlyEngine::Entities::Entity* entity, bool showMovement)
	{
		bool objectMoved = false;
		float sensibility = 1;
		float rotSensibility = 10;

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
		{
			entity->MoveForward(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_S))
		{
			entity->MoveBackward(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_SPACE))
		{
			entity->MoveUp(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			entity->MoveDown(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_A))
		{
			entity->MoveLeft(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_D))
		{
			entity->MoveRight(sensibility);
			objectMoved = true;
		}

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_I))
		{
			entity->Rotate(rotSensibility, 0.0f, 0.0f);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_K))
		{
			entity->Rotate(-rotSensibility, 0.0f, 0.0f);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_J))
		{
			entity->Rotate(0.0f, rotSensibility, 0.0f);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_L))
		{
			entity->Rotate(0.0f, -rotSensibility, 0.0f);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_U))
		{
			entity->Rotate(0.0f, 0.0f, -rotSensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_O))
		{
			entity->Rotate(0.0f, 0.0f, rotSensibility);
			objectMoved = true;
		}

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_ADD))
		{
			float scaleSens = 1.01f;
			entity->Scale(scaleSens, scaleSens, scaleSens);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_SUBTRACT))
		{
			float scaleSens = 0.99f;
			entity->Scale(-scaleSens, -scaleSens, -scaleSens);
			objectMoved = true;
		}


		if (objectMoved && showMovement)
		{
			std::string text = "- ";
			text += entity->GetName();
			text += " Updated Position : ";
			Debugger::ConsoleMessage(&text[0], entity->GetPosition());
		}
	}

}
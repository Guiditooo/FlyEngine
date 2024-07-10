#include <time.h>
#include <string>

#include "Game.h"

#include "MaterialManager/MaterialManager.h"
#include "ShaderManager/ShaderManager.h"

#include "FlyFunctions/Debugger/Debugger.h"
#include "TextureImporter/TextureImporter.h"
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
		pared1 = nullptr;
		pared2 = nullptr;
		cube = nullptr;
		pointLight = nullptr;
		pointLightStatic = nullptr;
		spotLight = nullptr;

		texture = nullptr;

		cameraController = nullptr;

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


		if (model != nullptr)
			delete model;
		model = nullptr;
	}
	
	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		mainCamera->SetPosition(0.0f, 1.0f, 5.0f);
		//mainCamera->SetRotation(-90, 0, 0);

		cameraController = CreateCameraController(mainCamera,0.05f, 0.2f, CameraMode::Free);

		piso = CreateRectangle(0, 0, 0, 1000, 1000);
		pared1 = CreateRectangle(0, 1000, -1000, 1000, 1000);
		pared2 = CreateRectangle(1000, 1000, 0, 1000, 1000);

		player = CreateCube(0, 1, 0, 100);
		cube = CreateCube(2, 1, 0, 100);

		piso->SetName("Piso");
		pared1->SetName("Pared1");
		pared2->SetName("Pared2");
		player->SetName("Player");
		cube->SetName("Cubo Uno");

		model = CreateModel("res/Models/Backpack/backpack.obj", "Backpack");
		model2 = CreateModel("res/Models/Barril/Barril.fbx", "Barril");
		model3 = CreateModel("res/Models/Delorean/delorean_low.fbx", "Delorean");
		model4 = CreateModel("res/Models/Iron Giant/irongiant_low.fbx", "Iron Giant");
		model5 = CreateModel("res/Models/Teapod/teapod.fbx", "teapod");

		pointLight = CreatePointLight(mainCamera->GetPosition());
		pointLightStatic = CreatePointLight();
		spotLight = CreateSpotLight(mainCamera->GetPosition(),-mainCamera->GetFront());

		pointLightStatic->SetName("Static Light");

		std::string boxMaterial = "Box_Mat";
		Managers::MaterialManager::CreateMaterial(boxMaterial);
		Materials::Material* boxMat = Managers::MaterialManager::GetMaterial(boxMaterial);

		boxMat->AddTexture("diffuse", CreateTexture("res/Textures/Box/Box.png"));
		boxMat->AddTexture("specular", CreateTexture("res/Textures/Box/Box_S.png"));
		boxMat->SetTextureOrder({ "diffuse", "specular" });

		player->SetMaterial(boxMat);
		piso->SetMaterial(boxMat);

		piso->SetRotation(-90, 0, 0);
		pared2->SetRotation(0, -90, 0);

		pointLightStatic->SetPosition(glm::vec3( 1, 5, 0));
		pointLightStatic->SetColor(COLOR::CYAN);

		piso->SetActive(true);
		pared1->SetActive(false);
		pared2->SetActive(false);
		player->SetActive(true);
		cube->SetActive(true);
		model->SetActive(true);
		model2->SetActive(true);
		model3->SetActive(true);
		model4->SetActive(true);
		model5->SetActive(true);
	}

	void Game::Update()
	{

		if (Input::GetKeyPressed(KeyCode::KEY_KP_1))
		{
			movingObject = MovingObject::Cube;
			Debugger::ConsoleMessage("Moving Cube");
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_2))
		{
			movingObject = MovingObject::Camera;
			Debugger::ConsoleMessage("Moving Camera");
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_3))
		{
			movingObject = MovingObject::Light;
			Debugger::ConsoleMessage("Moving Player");
		}

		CheckForEnabling(KeyCode::KEY_KP_7, KeyCode::KEY_KP_4, player);
		CheckForEnabling(KeyCode::KEY_KP_8, KeyCode::KEY_KP_5, model2);
		CheckForEnabling(KeyCode::KEY_KP_9, KeyCode::KEY_KP_6, model);

		CheckForEnabling(KeyCode::KEY_M, KeyCode::KEY_N, model3);
		CheckForEnabling(KeyCode::KEY_B, KeyCode::KEY_V, model4);
		CheckForEnabling(KeyCode::KEY_C, KeyCode::KEY_X, model5);


		switch (movingObject)
		{
		case FlyGame::MovingObject::Cube:
			MoveObject(model2, true);
			break;
		case FlyGame::MovingObject::Camera:
			cameraController->Update(false);
			spotLight->SetPosition(cameraController->GetCamera()->GetPosition());
			pointLight->SetPosition(cameraController->GetCamera()->GetPosition());
			spotLight->SetDirection(-cameraController->GetCamera()->GetFront());
			pointLight->SetDirection(-cameraController->GetCamera()->GetFront());
			break;
		case FlyGame::MovingObject::Light:
			MoveObject(model, true);
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
		float sensibility = 0.05;
		float rotSensibility = 1;

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
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_K))
		{
			entity->Rotate(-rotSensibility, 0.0f, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_J))
		{
			entity->Rotate(0.0f, rotSensibility, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_L))
		{
			entity->Rotate(0.0f, -rotSensibility, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_U))
		{
			entity->Rotate(0.0f, 0.0f, -rotSensibility);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_O))
		{
			entity->Rotate(0.0f, 0.0f, rotSensibility);
		}

		CheckForScaling(KeyCode::KEY_KP_ADD, KeyCode::KEY_KP_SUBTRACT, entity);


		if (objectMoved && showMovement)
		{
			std::string text = "- ";
			text += entity->GetName();
			text += " Updated Position : ";
			Debugger::ConsoleMessage(&text[0], entity->GetPosition());
		}

	}void Game::MoveObject(FlyEngine::Lights::Light* light, bool showMovement)
	{
		bool objectMoved = false;
		float sensibility = 0.05f;

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(0,0, -sensibility));
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_S))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(0, 0, sensibility));
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_SPACE))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(0, sensibility, 0));
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_LEFT_SHIFT))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(0, -sensibility, 0));
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_A))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(-sensibility, 0, 0));
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_D))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(sensibility, 0, 0));
			objectMoved = true;
		}


		if (objectMoved && showMovement)
		{
			std::string text = "- ";
			text += light->GetName();
			text += " Updated Position : ";
			Debugger::ConsoleMessage(&text[0], light->GetPosition());
		}
	}

	void Game::CheckForEnabling(KeyCode enableKey, KeyCode disableKey, Entities::Entity* thing)
	{
		if (Input::GetKeyPressed(enableKey))
		{
			thing->SetActive(true);
			Debugger::ConsoleMessage(thing->GetName(), true);
		}

		if (Input::GetKeyPressed(disableKey))
		{
			thing->SetActive(false);
			Debugger::ConsoleMessage(thing->GetName(), false);
		}
	}

	void Game::CheckForScaling(KeyCode maximizeKey, KeyCode minimizeKey, Entities::Entity* thing)
	{
		if (Input::GetKeyPressed(maximizeKey))
		{
			float scaleSens = 1.01f;
			thing->Scale(scaleSens);
		}
		if (Input::GetKeyPressed(minimizeKey))
		{
			float scaleSens = 0.99f;
			thing->Scale(scaleSens);
		}
	}

}
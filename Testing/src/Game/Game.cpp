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
		box = nullptr;
		piso = nullptr;
		pared1 = nullptr;
		pared2 = nullptr;
		box2 = nullptr;
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

		if (box != nullptr)
			delete box;
		box = nullptr;

		if (piso != nullptr)
			delete piso;
		piso = nullptr;

		if (box2 != nullptr)
			delete box2;
		box2 = nullptr;

		if (cameraController != nullptr)
			delete cameraController;
		cameraController = nullptr;


		if (backpack != nullptr)
			delete backpack;
		backpack = nullptr;
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

		box = CreateCube(0, 1, 0, 100);
		box2 = CreateCube(2, 1, 0, 100);

		piso->SetName("Piso");
		pared1->SetName("Pared1");
		pared2->SetName("Pared2");
		box->SetName("Player");
		box2->SetName("Cubo Uno");

		backpack = CreateModel("res/Models/Backpack/backpack.obj", "Backpack");

		barrel = CreateModel("res/Models/Barril/Barril.fbx", "Barril 1");
		barrel2 = CreateModel("res/Models/Barril/Barril.fbx", "Barril 2");
		barrel3 = CreateModel("res/Models/Barril/Barril.fbx", "Barril 3");

		delorean = CreateModel("res/Models/Delorean/delorean_low.fbx", "Delorean");
		ironGiant = CreateModel("res/Models/Iron Giant/irongiant_low.fbx", "Iron Giant");
		teapod = CreateModel("res/Models/Teapod/teapod.fbx", "teapod");

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

		box->SetMaterial(boxMat);
		box2->SetMaterial(boxMat);
		piso->SetMaterial(boxMat);

		box->SetScale(0.65f);
		box2->SetScale(0.2f);

		box->SetPosition(-0.745f, 0.3f, -0.88f);
		box2->SetPosition(-0.85f, 0.7f, -0.74f);

		std::string barrelMaterial = "Barrel_Mat";
		Managers::MaterialManager::CreateMaterial(barrelMaterial);
		Materials::Material* barrelMat = Managers::MaterialManager::GetMaterial(barrelMaterial);
		barrelMat->AddTexture("diffuse", CreateTexture("res/Models/Barril/diffuse.png"));
		barrelMat->AddTexture("specular", CreateTexture("res/Models/Barril/roughness.png"));
		barrelMat->SetTextureOrder({ "diffuse", "specular" });

		barrel->SetMaterial(barrelMat);
		barrel->UseBaseMaterial(true);
		barrel2->SetMaterial(barrelMat);
		barrel2->UseBaseMaterial(true);
		barrel3->SetMaterial(barrelMat);
		barrel3->UseBaseMaterial(true);

		barrel->SetScale(0.15f, 0.2f, 0.18f);
		barrel2->SetScale(0.14f, 0.14f, 0.14f);
		barrel3->SetScale(0.14f,0.16f,0.14f);

		barrel->SetPosition(1, 0, 0.93f);
		barrel2->SetPosition(1, 0, 0.55f);
		barrel3->SetPosition(0.65f, 0, 0.93f);

		piso->SetRotation(-90, 90, 0);
		pared2->SetRotation(0, -90, 0);

		teapod->SetColor(COLOR::GREY);
		teapod->SetScale(0.004f);
		teapod->SetRotation(-90, 0, 0);
		teapod->SetPosition(-0.52f, 0.62f, -0.675f);

		delorean->SetColor(COLOR::MAGENTA);
		delorean->SetScale(0.08f);
		delorean->SetRotation(0, -30, 0);
		delorean->SetPosition(-0.11f, 0.27f, 0.36f);

		ironGiant->SetColor(COLOR::LIGHT_GREY);
		ironGiant->SetScale(0.004f);
		ironGiant->SetRotation(0, -30, 0);
		ironGiant->SetPosition(1,0,-1);

		backpack->SetScale(0.2f);
		backpack->SetRotation(-171.969214f, 19.2966456f, -176.649076f);
		backpack->SetPosition(1.147006f, 1.059893f, -1.274624f);

		pointLightStatic->SetPosition(glm::vec3( 1, 5, 0));
		pointLightStatic->SetColor(COLOR::CYAN);

		piso->SetActive(true);
		pared1->SetActive(false);
		pared2->SetActive(false);
		box->SetActive(true);
		box2->SetActive(true);
		backpack-> SetActive(true); //Mochila
		barrel->SetActive(true); //Barril
		barrel2->SetActive(true); //Barril
		barrel3->SetActive(true); //Barril
		delorean->SetActive(true); //Delorean
		ironGiant->SetActive(true); //Gigante
		teapod->SetActive(true); //Tetera
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

		CheckForEnabling(KeyCode::KEY_KP_7, KeyCode::KEY_KP_4, box);
		CheckForEnabling(KeyCode::KEY_KP_8, KeyCode::KEY_KP_5, barrel);
		CheckForEnabling(KeyCode::KEY_KP_9, KeyCode::KEY_KP_6, backpack);

		CheckForEnabling(KeyCode::KEY_M, KeyCode::KEY_N, delorean);
		CheckForEnabling(KeyCode::KEY_B, KeyCode::KEY_V, ironGiant);
		CheckForEnabling(KeyCode::KEY_C, KeyCode::KEY_X, teapod);


		switch (movingObject)
		{
		case FlyGame::MovingObject::Cube:
			MoveObject(backpack, true);
			break;
		case FlyGame::MovingObject::Camera:
			cameraController->Update(false);
			spotLight->SetPosition(cameraController->GetCamera()->GetPosition());
			pointLight->SetPosition(cameraController->GetCamera()->GetPosition());
			spotLight->SetDirection(-cameraController->GetCamera()->GetFront());
			pointLight->SetDirection(-cameraController->GetCamera()->GetFront());
			break;
		case FlyGame::MovingObject::Light:
			MoveObject(ironGiant, true);
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
		float sensibility = 0.01f;
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
//#include <time.h>
#include <string>

#include "Game.h"

#include "MaterialManager/MaterialManager.h"
#include "TextureManager/TextureManager.h"

#include "FlyFunctions/Debugger/Debugger.h"
//#include "MaterialSpecification/MaterialSpecification.h"

namespace FlyGame
{
	//using namespace std;

	bool movingPlayer = true;

	Game::Game(int width, int height, std::string name)
	{
		SetWindowParameters(width, height, name);

		cameraController = nullptr;

		piso = nullptr;
		pointLight = nullptr;
		pointLightStatic = nullptr;
		spotLight = nullptr;

		texture = nullptr;

		movingEntity = nullptr;

		cameraController = nullptr;

		movingObject = MovingObject::Cube;

		SetEngineMode(EngineMode::Engine3D);
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		//cameraController = CreateCameraController(mainCamera, 0.05f, 0.2f, CameraMode::Free);

		piso = CreateRectangle(0, 0, 0, 1000, 1000);

		triangle = CreateTriangle(0, 1, 0, 10, 10);

		cube = CreateCube(0, 1, 0, 50);
		cube->SetName("BOX");

		piso->SetName("Piso");
		triangle->SetName("Player");

		pointLight = CreatePointLight(mainCamera->GetTransform()->GetPosition());
		pointLightStatic = CreatePointLight();
		spotLight = CreateSpotLight(mainCamera->GetTransform()->GetPosition(), -mainCamera->GetTransform()->GetFront());

		pointLightStatic->SetName("Static Light");

		pointLightStatic->SetPosition(glm::vec3(1, 5, 0));
		pointLightStatic->SetColor(COLOR::CYAN);

		spotLight->SetPosition(glm::vec3(0, 2, 0));
		spotLight->SetDirection(piso->GetTransform()->GetPosition() - spotLight->GetPosition());

		std::string boxMaterial = "Box_Mat";
		
		Managers::TextureManager::CreateTexture("Box", "res/Textures/Box"); //TODO HACER FACADE DESDE EL BASEGAME
		Managers::TextureManager::CreateTexture("Box_S", "res/Textures/Box");

		Managers::MaterialManager::CreateMaterial(boxMaterial, Managers::ShaderManager::GetDefaultModelShader());
		Managers::MaterialManager::AddTexture(boxMaterial, "diffuse", Managers::TextureManager::GetTexture("Box"));
		Managers::MaterialManager::AddTexture(boxMaterial, "specular", Managers::TextureManager::GetTexture("Box_S"));
		Managers::MaterialManager::SetTextureOrder(boxMaterial, { "diffuse", "specular" });

		Materials::Material* boxMat = Managers::MaterialManager::GetMaterial(boxMaterial);

		piso->SetMaterial(boxMat);
		piso->SetScale(100, 100, 100);
		piso->SetRotation(-90, 90, 0);

		Managers::MaterialManager::CreateMaterial("Carito", Managers::ShaderManager::GetDefaultModelShader());
		Managers::MaterialManager::AddTexture("Carito", "diffuse", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::AddTexture("Carito", "specular", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::AddTexture("Carito", "normal", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::SetTextureOrder(boxMaterial, { "diffuse", "specular", "normal"});

		Materials::Material* caritoMat = Managers::MaterialManager::GetMaterial("Carito");

		caritoMat->SetSpecs(Materials::MaterialList::Ruby);

		cube->SetMaterial(caritoMat);

		//cube->SetColor(COLOR::MAGENTA);

		piso->SetActive(true);
		triangle->SetActive(false);
		cube->SetActive(true);

	}

	void Game::Update()
	{
		if (Input::GetKeyPressed(KeyCode::KEY_1))
		{
			cameraController->SetMouseMovementOn(true);
			HideCursor();
		}
		if (Input::GetKeyPressed(KeyCode::KEY_2))
		{
			cameraController->SetMouseMovementOn(false);
			ShowCursor();
		}

		//if (Input::GetKeyPressed(KeyCode::KEY_1))
		//{
		//	if (movingEntity != nullptr)
		//		cameraController->SetFirstTarget(movingEntity);
		//}
		//
		//if (Input::GetKeyPressed(KeyCode::KEY_2))
		//{
		//	cameraController->SetMode(CameraMode::Free);
		//}

		if (Input::GetKeyPressed(KeyCode::KEY_3))
		{
			//if (movingEntity != nullptr)
				//cameraController->SetThirdTarget(movingEntity, 5);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_0))
		{
			SetEngineMode(EngineMode::Engine2D);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_9))
		{
			SetEngineMode(EngineMode::Only2D);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_8))
		{
			SetEngineMode(EngineMode::Engine3D);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_7))
		{
			SetEngineMode(EngineMode::Only3D);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_1))
		{
			movingEntity = triangle;
			movingObject = MovingObject::Player;
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_2))
		{

		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_3))
		{

		}

		CheckForEnabling(KeyCode::KEY_RIGHT, KeyCode::KEY_LEFT, GetDirectionalLight());
		CheckForEnabling(KeyCode::KEY_UP, KeyCode::KEY_DOWN, spotLight);
		CheckForEnabling(KeyCode::KEY_T, KeyCode::KEY_G, pointLight);
		CheckForEnabling(KeyCode::KEY_R, KeyCode::KEY_F, pointLightStatic);

		//cameraController->SetMode(CameraMode::Free);

		if (movingEntity != nullptr)
		{
			if (movingObject == MovingObject::Camera)
			{
				MoveObject(spotLight);
			}

			else
			{
				MoveObject(movingEntity);
			}
		}

		cameraController->Update(false);

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
			entity->GetTransform()->Rotate(rotSensibility, 0.0f, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_K))
		{
			entity->GetTransform()->Rotate(-rotSensibility, 0.0f, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_J))
		{
			entity->GetTransform()->Rotate(0.0f, rotSensibility + entity->GetTransform()->GetRotation().y, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_L))
		{
			entity->GetTransform()->Rotate(0.0f, -rotSensibility + entity->GetTransform()->GetRotation().y, 0.0f);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_U))
		{
			entity->GetTransform()->Rotate(0.0f, 0.0f, -rotSensibility);
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_O))
		{
			entity->GetTransform()->Rotate(0.0f, 0.0f, rotSensibility);
		}

		CheckForScaling(KeyCode::KEY_KP_ADD, KeyCode::KEY_KP_SUBTRACT, entity);


		if (objectMoved && showMovement)
		{
			std::string text = "- ";
			text += entity->GetName();
			text += " Updated Position : ";
			Debugger::ConsoleMessage(&text[0], entity->GetTransform()->GetPosition());
		}

	}void Game::MoveObject(FlyEngine::Lights::Light* light, bool showMovement)
	{
		bool objectMoved = false;
		float sensibility = 0.05f;

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_W))
		{
			light->SetPosition(light->GetPosition() + glm::vec3(0, 0, -sensibility));
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
	void Game::CheckForEnabling(KeyCode enableKey, KeyCode disableKey, Lights::Light* light)
	{
		if (Input::GetKeyPressed(enableKey))
		{
			light->SetActive(true);
			Debugger::ConsoleMessage(light->GetName(), true);
		}

		if (Input::GetKeyPressed(disableKey))
		{
			light->SetActive(false);
			Debugger::ConsoleMessage(light->GetName(), false);
		}
	}

	void Game::CheckForScaling(KeyCode maximizeKey, KeyCode minimizeKey, Entities::Entity* thing)
	{
		if (Input::GetKeyPressed(maximizeKey))
		{
			float scaleSens = 1.01f;
			thing->GetTransform()->Scale(scaleSens);
		}
		if (Input::GetKeyPressed(minimizeKey))
		{
			float scaleSens = 0.99f;
			thing->GetTransform()->Scale(scaleSens);
		}
	}

	void Game::SetCameraTarget(Entities::Entity* target, CameraMode mode)
	{
		/*
		cameraController->SetMode(mode);
		movingEntity = target;
		if(cameraController->GetTarget()!=nullptr)
			cameraController->GetTarget()->SetAsCameraTarget(false);
		cameraController->SetTarget(target);
		target->SetAsCameraTarget(true);
		MoveObject(target);
		*/
	}

}
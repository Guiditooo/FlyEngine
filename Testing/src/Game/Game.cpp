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

		movingEntity = nullptr;

		cameraController = nullptr;

		movingObject = MovingObject::Cube;

		SetEngineMode(EngineMode::Only2D);
	}

	Game::~Game()
	{

	}

	void Game::Init()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		//cameraController = CreateCameraController(mainCamera, 0.05f, 0.2f, CameraMode::Free);

		//scene1 = CreateModel("res/Models/Scene/Guido_scene.fbx", "BSP_Scene1");
		//scene2 = CreateModel("res/Models/Scene/PruebaGuido.fbx", "BSP_Scene2");
		//scene3->SetColor(COLOR::MAGENTA);
		//scene3->GetTransform()->SetWorldScale(3, 3, 3);

		//robot = CreateModel("res/Models/Iron_Giant/irongiant_low.fbx", "Robot1");
		cubos = CreateModel("res/Models/Cubos/CubitoDubiDuuu.fbx", "Cubos");
		//scene3 = CreateModel("res/Models/Scene/planes_scene.fbx", "BSP_Scene3");
		//silla = CreateModel("res/Models/Silla/Silla.fbx", "Silla");
		//bp = CreateModel("res/Models/Backpack/backpack.obj", "BP");

		//bp->GetTransform()->SetWorldScale(0.05f, 0.05f, 0.05f);
		//bp->GetTransform()->SetWorldPosition(0, 0.1, 0.8f);

		cubos->GetTransform()->SetWorldScale(2, 2, 2);

		//scene3->GetTransform()->SetWorldScale(10, 1, 10);

		//silla->GetTransform()->SetWorldScale(6, 6, 6);
		//silla->GetTransform()->SetWorldPosition(0, 0.1, -0.8f);

		cubos->SetMaterial(Managers::MaterialManager::GetDefaultModelMaterial(), true);
		cubos->SetColor(COLOR::RED);
		
		//robot->SetColor(COLOR::BLACK);

		piso = CreateRectangle(0, 0, 0, 1000, 1000);

		triangle = CreateTriangle(0, 1, 0, 10, 10);
		rectangle = CreateRectangle(0, 0, 0, 10, 10);

		cube = CreateCube(0, 1, 0, 500);
		cube->SetName("BOX");

		piso->SetName("Piso");
		triangle->SetName("Player");

		pointLight = CreatePointLight(mainCamera->GetTransform()->GetWorldPosition());
		pointLightStatic = CreatePointLight();
		spotLight = CreateSpotLight(mainCamera->GetTransform()->GetWorldPosition(), -mainCamera->GetTransform()->GetFront());

		pointLightStatic->SetName("Static Light");

		pointLightStatic->SetPosition(glm::vec3(1, 5, 0));
		//pointLightStatic->SetColor(COLOR::CYAN);

		spotLight->SetPosition(glm::vec3(0, 3, 0));
		spotLight->SetDirection(glm::vec3(0, 0, 0));

		std::string boxMaterial = "Box_Mat";

		Managers::TextureManager::CreateTexture("Box", "res/Textures/Box"); //TODO HACER FACADE DESDE EL BASEGAME
		Managers::TextureManager::CreateTexture("Box_S", "res/Textures/Box");

		Managers::MaterialManager::CreateMaterial(boxMaterial, Managers::ShaderManager::GetDefaultModelShader());
		Managers::MaterialManager::AddTexture(boxMaterial, "diffuse", Managers::TextureManager::GetTextureID("Box"));
		Managers::MaterialManager::AddTexture(boxMaterial, "specular", Managers::TextureManager::GetTextureID("Box_S"));
		Managers::MaterialManager::SetTextureOrder(boxMaterial, { "diffuse", "specular" });

		Materials::Material* boxMat = Managers::MaterialManager::GetMaterial(boxMaterial);

		//piso->SetMaterial(boxMat);
		piso->GetTransform()->SetWorldScale(100, 100, 100);
		piso->GetTransform()->SetWorldRotation(-90, 90, 0);

		Managers::MaterialManager::CreateMaterial("Carito", Managers::ShaderManager::GetDefaultModelShader());
		Managers::MaterialManager::AddTexture("Carito", "diffuse", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::AddTexture("Carito", "specular", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::AddTexture("Carito", "normal", Managers::TextureManager::GetDefaultTextureID());
		Managers::MaterialManager::SetTextureOrder(boxMaterial, { "diffuse", "specular", "normal" });

		Materials::Material* caritoMat = Managers::MaterialManager::GetMaterial("Carito");

		caritoMat->SetSpecs(Materials::MaterialList::Ruby);

		//cube->SetMaterial(caritoMat);
		cube->SetMaterial(boxMat, true);
		
		//cube->SetColor(COLOR::MAGENTA);
		//robot->SetMaterial(boxMat, true);

		//silla->SetActive(true);
		cubos->SetActive(false);
		//robot->SetActive(false);
		//scene3->SetActive(true);
		
		piso->SetActive(false);
		triangle->SetActive(false);
		rectangle->SetActive(true);
		cube->SetActive(false);

		//int hTexID = Managers::TextureManager::CreateTexture("facha2", "res/Textures");

		//Managers::MaterialManager::CreateMaterial("HMaterial", Managers::ShaderManager::GetDefaultBasicShader());
		//Managers::MaterialManager::AddTexture("HMaterial", "diffuse", hTexID);
		//Managers::MaterialManager::SetTextureOrder("HMaterial", { "diffuse" });
		//Materials::Material* hMat = Managers::MaterialManager::GetMaterial("HMaterial");
		//rectangle->SetMaterial(hMat,false);

		rectangle->GetTransform()->WorldScale(3,5,3);

		Entities::Sprite* s = CreateSprite("res/Textures/facha2.jpeg",true);

	}

	void Game::Update()
	{
		//MoveObject(spotLight);
		//spotLight->SetDirection(mainCamera->GetTransform()->GetFront());
		//spotLight->SetPosition(mainCamera->GetTransform()->GetWorldPosition());


		if (Input::GetKeyPressed(KeyCode::KEY_1))
		{
			if(engineMode==EngineMode::Engine3D || engineMode == EngineMode::Only3D)
				cameraController->SetMouseMovementOn(true);
			
			HideCursor();
		}
		if (Input::GetKeyPressed(KeyCode::KEY_2))
		{
			if (engineMode == EngineMode::Engine3D || engineMode == EngineMode::Only3D)
				cameraController->SetMouseMovementOn(false);
			ShowCursor();
		}
		
		if (Input::GetKeyPressed(KeyCode::KEY_P))
		{
			//Entities::Entity* cubito3 = cubos->GetChildrenWithName("Cubito16")[0];
			//cubito3->GetTransform()->LocalRotate(0, 0.05, 0);
			//Debugger::ConsoleMessage("BB MIN >", cubos->GetWorldBoundingBox().min);
			//Debugger::ConsoleMessage("BB MAX >", cubos->GetWorldBoundingBox().max);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_O))
		{
			//Entities::Entity* cubito3 = cubos->GetChildrenWithName("Cubito16")[0];
			//cubito3->GetTransform()->LocalRotate(0, -0.05, 0);
			//Debugger::ConsoleMessage("BB MIN >", cubos->GetWorldBoundingBox().min);
			//Debugger::ConsoleMessage("BB MAX >", cubos->GetWorldBoundingBox().max);
		}
		
		//MoveObject(cubos/*->GetChildrenWithName("Cubito3")[0]*/);

		if (Input::GetKeyPressed(KeyCode::KEY_3))
		{

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

		if (Input::GetKeyPressed(KeyCode::KEY_KP_1))
		{
			//cubos->GetChildrenWithName("Cubito2")[0]->GetTransform()->LocalRotate(0, 0.1, 0);
		}

		if (Input::GetKeyPressed(KeyCode::KEY_KP_3))
		{
			//cubos->GetChildrenWithName("Cubito2")[0]->GetTransform()->LocalRotate(0, -0.1, 0);
		}

		//CheckForEnabling(KeyCode::KEY_RIGHT, KeyCode::KEY_LEFT, silla);
		//CheckForEnabling(KeyCode::KEY_UP, KeyCode::KEY_DOWN, spotLight);
		//CheckForEnabling(KeyCode::KEY_T, KeyCode::KEY_G, pointLight);
		//CheckForEnabling(KeyCode::KEY_R, KeyCode::KEY_F, pointLightStatic);

		//CheckForScaling(KeyCode::KEY_KP_ADD, KeyCode::KEY_KP_SUBTRACT, cubos->GetChildrenWithName("Cubito3")[0]);

		//cameraController->SetMode(CameraMode::Free);ee

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

		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_8))
		{
			entity->MoveForward(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_2))
		{
			entity->MoveBackward(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_0))
		{
			entity->MoveUp(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_5))
		{
			entity->MoveDown(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_4))
		{
			entity->MoveLeft(sensibility);
			objectMoved = true;
		}
		if (Input::GetKeyPressed(Utils::KeyCode::KEY_KP_6))
		{
			entity->MoveRight(sensibility);
			objectMoved = true;
		}
		/*
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
		*/


		if (objectMoved && showMovement)
		{
			std::string text = "- ";
			text += entity->GetName();
			text += " Updated Position : ";
			Debugger::ConsoleMessage(&text[0], entity->GetTransform()->GetWorldPosition());
		}

	}
	
	void Game::MoveObject(FlyEngine::Lights::Light* light, bool showMovement)
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
			thing->GetTransform()->WorldScale(scaleSens, scaleSens, scaleSens);
		}
		if (Input::GetKeyPressed(minimizeKey))
		{
			float scaleSens = 0.99f;
			thing->GetTransform()->WorldScale(scaleSens, scaleSens, scaleSens);
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
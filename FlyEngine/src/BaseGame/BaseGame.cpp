#include "BaseGame.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer/Renderer.h"

#include "TextureImporter/TextureImporter.h"
#include "ModelImporter/ModelImporter.h"

#include "MaterialManager/MaterialManager.h"

#include "Material/Material.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include "FlyFunctions/Commons/Commons.h"
#include "FlyFunctions/ColorCode/ColorCode.h"

#include "Input/Input.h"
#include "Lights/LightType.h"


//static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
//FlyEngine::CameraController* newCamera;
//bool isFirstTime = true;
//static double lastMouseX;
//static double  lastMouseY;

template <typename T>
static void EraseList(std::list<T*>& list);

namespace FlyEngine
{

	using namespace Managers;

	void FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	BaseGame::BaseGame()
	{
		window = nullptr;
		mainCamera = nullptr;

		renderer = nullptr;

		initialWindowName = "FlyEngine";
		initialWindowWidth = 0;
		initialWindowHeight = 0;
		checkEsc = true;

		//isFirstTime = true;

		using3DEntities = true;
		using2DEntities = true;
		calculatingLights = true;

		isRunning = false;
		directionalLight = CreateDirectionalLight();
		Importers::TextureImporter::Init(true);
	}

	BaseGame::~BaseGame()
	{
		if (mainCamera != nullptr)
			delete mainCamera;
		mainCamera = nullptr;

		if (window != nullptr)
			delete window;
		window = nullptr;

		if (renderer != nullptr)
			delete renderer;
		renderer = nullptr;

		CameraController::DestroyInstance();

		EraseList(modelList);
		EraseList(entity3DList);
		EraseList(entity2DList);
		EraseList(lightList);
		EraseList(textureList);
	}

	void BaseGame::SetWindowParameters(int width, int height, std::string name)
	{
		initialWindowWidth = width;
		initialWindowHeight = height;
		initialWindowName = name;
	}

	glm::vec2 BaseGame::GetWindowSize()
	{
		return window->GetWindowSize();
	}

	Camera* BaseGame::GetMainCamera()
	{
		return mainCamera;
	}

	void BaseGame::CreateBuffers(Buffers* buffers)
	{
		renderer->CreateBaseBuffers(*buffers);
	}

	void BaseGame::BindBuffers(Buffers* buffers, std::vector<float> vertex, std::vector<unsigned int> index)
	{
		renderer->BindBuffers(*buffers, vertex, vertex.size(), index, index.size());
	}

	void BaseGame::SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes)
	{
		renderer->SetVertexAttributes(vertexAttributes);
	}

	void BaseGame::DrawObjects()
	{
		if (calculatingLights)
			CalculateLights();
		if (using2DEntities)
			Draw2DEntities();
		if (using3DEntities)
			Draw3DEntities();
	}

	void BaseGame::DrawModels()
	{
		for (Entities::Model* model : modelList)
		{
			if (model->IsActive())
			{
				renderer->DrawModel(model, mainCamera->GetViewMatrix(), mainCamera->GetProjMatrix(), mainCamera->GetTransform()->GetPosition());
			}
		}
	}

	void BaseGame::Draw2DEntities()
	{
		for (Entities::Entity* entity : entity2DList)
		{
			if (entity->IsActive() && !entity->IsCameraTarget())
			{
				entity->UseShader();
				SetMatrixUniforms(entity);

				SetMaterialUniforms(entity);
				renderer->SetVec3Uniform(entity->GetShaderID(), "baseColor", entity->GetColor().GetColorV3());
				renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
			}
		}
	}

	void BaseGame::Draw3DEntities()
	{
		for (Entities::Entity* entity : entity3DList)
		{
			if (dynamic_cast<Entities::Model*>(entity) != nullptr)
			{
				renderer->DrawModel(dynamic_cast<Entities::Model*>(entity), mainCamera->GetViewMatrix(), mainCamera->GetProjMatrix(), mainCamera->GetTransform()->GetPosition());
			}
			else
			{
				if (entity->IsActive() && !entity->IsCameraTarget())
				{
					entity->UseShader();
					SetMatrixUniforms(entity);

					SetMaterialUniforms(entity);
					renderer->SetVec3Uniform(entity->GetShaderID(), "baseColor", entity->GetColor().GetColorV3());
					renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
				}
			}
		}
	}


	void BaseGame::CalculateLights()
	{
		int pointLightIndex = 0;
		for (Lights::Light* light : lightList)
		{
			if (pointLightIndex < MAX_POINT_LIGHTS)//Cambiar por una constante
			{
				SetLightUniforms(light, pointLightIndex);
				if (light->GetLightType() == Lights::LightType::Point)
					pointLightIndex++;
			}
		}
	}

	void BaseGame::SetMatrixUniforms(Entities::Entity* entity)
	{
		unsigned int id = entity->GetShaderID();
		renderer->SetMatrix4Uniform(id, "view", mainCamera->GetViewMatrix());
		renderer->SetMatrix4Uniform(id, "projection", mainCamera->GetProjMatrix());
		renderer->SetMatrix4Uniform(id, "model", entity->GetModelMatrix());
		renderer->SetVec3Uniform(id, "viewPos", mainCamera->GetTransform()->GetPosition());
	}

	void BaseGame::SetLightUniforms(Lights::Light* light, int index, unsigned int shaderID)
	{
		switch (light->GetLightType())
		{
		case Lights::LightType::Directional:
			renderer->SetDirectionalLight((Lights::DirectionalLight*)light, shaderID);
			break;
		case Lights::LightType::Point:
			renderer->SetPointLight((Lights::PointLight*)light, index, shaderID);
			break;
		case Lights::LightType::Spot:
			renderer->SetSpotLight((Lights::SpotLight*)light, shaderID);
			break;
		default:
			break;
		}
	}

	void BaseGame::SetMaterialUniforms(Entities::Entity* entity)
	{
		unsigned int id = entity->GetShaderID();
		Materials::Material* mat = entity->GetMaterial();

		mat->ApplyTextures();
		renderer->SetIntUniform(id, "material.diffuse", 0);
		renderer->SetIntUniform(id, "material.specular", 1);
		renderer->SetFloatUniform(id, "material.shininess", 64);
	}

	float BaseGame::PixelsToEngine(int objectWidthInPixels, float windowDimension)
	{
		return (objectWidthInPixels * 1.0f) / windowDimension;
	}


	void BaseGame::GetMouseMovement()
	{

	}

	Entities::Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width, float height)
	{
		Entities::Rectangle* rec = new Entities::Rectangle();
		glm::vec2 windowSize = window->GetWindowSize();

		rec->SetPosition(PixelsToEngine(posX, windowSize.x), PixelsToEngine(posY, windowSize.x), PixelsToEngine(posZ, windowSize.x));
		rec->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(height, windowSize.x), 1);

		rec->SetMaterial(MaterialManager::GetDefaultBasicMaterial());

		CreateBuffers(rec->GetBuffers());
		BindBuffers(rec->GetBuffers(), rec->GetVertexList(), rec->GetIndexList());
		SetVertexAttributes(rec->GetVertexAttributes());

		entity2DList.push_back(rec);

		return rec;
	}

	Entities::Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width)
	{
		return CreateRectangle(posX, posY, posZ, width, width);
	}

	Entities::Triangle* BaseGame::CreateTriangle(float posX, float posY, float posZ, float base, float height)
	{
		Entities::Triangle* tri = new Entities::Triangle();
		glm::vec2 windowSize = window->GetWindowSize();

		tri->SetPosition(PixelsToEngine(posX, windowSize.x), PixelsToEngine(posY, windowSize.x), PixelsToEngine(posZ, windowSize.x));
		tri->SetScale(PixelsToEngine(base, windowSize.x), PixelsToEngine(height, windowSize.x), 1);

		tri->SetMaterial(MaterialManager::GetDefaultBasicMaterial());

		CreateBuffers(tri->GetBuffers());
		BindBuffers(tri->GetBuffers(), tri->GetVertexList(), tri->GetIndexList());
		SetVertexAttributes(tri->GetVertexAttributes());

		entity2DList.push_back(tri);

		return tri;
	}

	Entities::Cube* BaseGame::CreateCube(float posX, float posY, float posZ, float width)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Entities::Cube* cube = new Entities::Cube();
		cube->SetPosition(posX, posY, posZ);
		cube->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x));

		cube->SetMaterial(MaterialManager::GetDefaultModelMaterial());

		CreateBuffers(cube->GetBuffers());
		BindBuffers(cube->GetBuffers(), cube->GetVertexList(), cube->GetIndexList());
		SetVertexAttributes(cube->GetVertexAttributes());
		entity3DList.push_back(cube);
		return cube;
	}

	Lights::DirectionalLight* BaseGame::CreateDirectionalLight(glm::vec3 direction)
	{
		Lights::DirectionalLight* light = new Lights::DirectionalLight();
		light->SetColor(FlyEngine::Utils::COLOR::WHITE);
		light->SetDirection(direction);
		lightList.push_back(light);
		return light;
	}

	Lights::PointLight* BaseGame::CreatePointLight(glm::vec3 position)
	{
		Lights::PointLight* light = new Lights::PointLight();
		light->SetColor(FlyEngine::Utils::COLOR::WHITE);
		light->SetPosition(position);
		lightList.push_back(light);
		return light;
	}

	Lights::SpotLight* BaseGame::CreateSpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff)
	{
		Lights::SpotLight* light = new Lights::SpotLight();
		light->SetColor(FlyEngine::Utils::COLOR::WHITE);
		light->SetPosition(position);
		light->SetDirection(direction);
		light->SetCutOff(cutOff);
		light->SetOuterCutOff(outerCutOff);
		lightList.push_back(light);
		return light;
	}

	Lights::DirectionalLight* BaseGame::GetDirectionalLight()
	{
		return directionalLight;
	}

	void BaseGame::ShowCursor()
	{
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void BaseGame::HideCursor()
	{
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void BaseGame::Toggle3DEntityEnabled(bool value)
	{
		using3DEntities = value;
	}

	void BaseGame::Toggle2DEntityEnabled(bool value)
	{
		using2DEntities = value;
	}

	void BaseGame::ToggleLightCalculations(bool value)
	{
		calculatingLights = value;
	}

	void BaseGame::SetEngineMode(EngineMode mode)
	{
		CameraController* CC = FlyEngine::CameraController::GetInstance();

		engineMode = mode;
		switch (engineMode)
		{
		case EngineMode::Engine3D:
			if (mainCamera != nullptr)
				mainCamera->SetProjectionType(ProjectionType::Perspective);
			if (CC != nullptr)
				CC->SetMouseMovementOn(true);
			using3DEntities = true;
			using2DEntities = true;
			break;
		case EngineMode::Engine2D:
			if (mainCamera != nullptr)
				mainCamera->SetProjectionType(ProjectionType::Ortho);
			if (CC != nullptr)
				CC->SetMouseMovementOn(false);
			using3DEntities = true;
			using2DEntities = true;
			break;
		case EngineMode::Only3D:
			if (mainCamera != nullptr)
				mainCamera->SetProjectionType(ProjectionType::Perspective);
			if (CC != nullptr)
				CC->SetMouseMovementOn(true);
			using3DEntities = true;
			using2DEntities = false;
			break;
		case EngineMode::Only2D:
			if (mainCamera != nullptr)
				mainCamera->SetProjectionType(ProjectionType::Ortho);
			if (CC != nullptr)
				CC->SetMouseMovementOn(false);
			using3DEntities = false;
			using2DEntities = true;
			break;
		default:
			break;
		}
	}

	void BaseGame::InternalInit()
	{
		Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);

		if (glfwInit() == GLFW_FALSE)
		{
			Debugger::ConsoleMessage("Error on GLFW initializating", 2, 0, 1, 0);
			Debugger::ConsoleMessage("Stopping execution!", 2, 0, 1, 0);
			return;
		}
		else
		{
			Debugger::ConsoleMessage("GLFW Loaded Successfully", 2, 0, 1, 2);
		}

		if (initialWindowHeight < 0 || initialWindowWidth < 0)
		{
			window = new Window(initialWindowName);
		}
		else
		{
			window = new Window(initialWindowWidth, initialWindowHeight, initialWindowName);
		}
		if (!window)
		{
			Debugger::ConsoleMessage("Error: Window Not Found", 2, 0, 1, 0);
			return;
		}

		mainCamera = new Camera();

		SetUpOpenGlFunctions();

		Input::SetContextWindow(window);

		renderer = new Renderer();

		cameraController = CameraController::Initialize(mainCamera, window);

		glfwSetCursorPosCallback(window->GetWindow(), CameraController::MouseCallback);

		Init();
	}

	void BaseGame::InternalUpdate()
	{
		GetMouseMovement();
		renderer->SetBackgroundColor(Color::GetColor(FlyEngine::COLOR::MOSS_GREEN));
		if (checkEsc)
		{
			if (Input::GetKeyPressed(KeyCode::KEY_ESCAPE))
			{
				glfwSetWindowShouldClose((window->GetWindow()), true);
			}
		}
		Update();
	}

	void BaseGame::InternalDraw()
	{
		DrawObjects();
		SwapBuffers();
	}

	void BaseGame::InternalDeinit()
	{
		Deinit();

		glfwTerminate();

		FlyEngine::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
	}

	void BaseGame::SwapBuffers()
	{
		glfwSwapBuffers(window->GetWindow());
	}

	void BaseGame::SetUpOpenGlFunctions()
	{
		glfwMakeContextCurrent(window->GetWindow());
		glfwSetFramebufferSizeCallback(window->GetWindow(), FrameBufferResizeCallback);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
		glEnable(GL_SAMPLE_ALPHA_TO_ONE);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND); //Transparency
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.1f);

		if (glewInit() != GLEW_OK)
			Debugger::ConsoleMessage("GLEW FAILED!", 2, 0, 1, 1);
	}

	void BaseGame::RunGame()
	{
		isRunning = true;
		InternalInit();

		while (isRunning && !glfwWindowShouldClose(window->GetWindow()))
		{
			glfwPollEvents();
			Input::Update();
			InternalUpdate();
			InternalDraw();
		}

		InternalDeinit();
	}

	bool BaseGame::IsGameRunning()
	{
		return isRunning;
	}

	void BaseGame::ToggleClosingWithEsc()
	{
		checkEsc = !checkEsc;
	}

	Texture* BaseGame::CreateTexture(const char* path)
	{
		return Importers::TextureImporter::LoadTexture(path, true);
	}

	CameraController* BaseGame::CreateCameraController(Camera* controllingCamera, float translateSens, float rotationSens, CameraMode cameraMode, Entities::Entity* target, float followDistance)
	{
		CameraController* CC = FlyEngine::CameraController::GetInstance();
		
		if (CC == nullptr)
		{
			CC->Initialize(controllingCamera, window); 
		}
		
		CC->SetMode(cameraMode);
		CC->SetObjetiveParameters(new ObjetiveParams(target, followDistance));

		std::string text = "CameraController Created!";
		Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);

		return CC;
	}


	Entities::Model* BaseGame::CreateModel(std::string const& path, std::string name)
	{
		Entities::Model* model = Importers::ModelImporter::LoadModel(name, path);

		//glm::vec3 dims = model->GetDimesions();
		//float middleNumber = FindMiddleNumber(dims.x, dims.y, dims.z);
		//float windowSize = window->GetWindowSize().x;
		//float newScale = PixelsToEngine(middleNumber, windowSize);

		//model->SetScale(newScale, newScale, newScale);

		//CreateBuffers(model->GetBuffers());
		//BindBuffers(model->GetBuffers(), model->GetVertexList(), rec->GetIndexList());
		//SetVertexAttributes(rec->GetVertexAttributes());

		std::string text = "Model Loaded: (" + model->GetName() + ")!";
		Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);
		modelList.push_back(model);
		entity3DList.push_back(model);
		return model;
	}

	float BaseGame::FindMiddleNumber(float a, float b, float c)
	{
		float maxVal = std::max({ a, b, c });
		float minVal = std::min({ a, b, c });

		// La mediana es el valor que no es ni el máximo ni el mínimo
		if ((a != maxVal) && (a != minVal))
		{
			return a;
		}
		if ((b != maxVal) && (b != minVal))
		{
			return b;
		}
		return c;
	}

}

template<typename T>
static void EraseList(std::list<T*>& list)
{
	for (auto element : list)
	{
		if (element != nullptr)
			delete element;
		element = nullptr;
	}
	list.clear();
}

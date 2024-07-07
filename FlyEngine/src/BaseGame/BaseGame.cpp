#include "BaseGame.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer/Renderer.h"

#include "TextureImporter/TextureImporter.h"
#include "ModelImporter/ModelImporter.h"

#include "Material/Material.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include "FlyFunctions/Commons/Commons.h"
#include "FlyFunctions/ColorCode/ColorCode.h"
#include "MaterialSpecification/MaterialSpecification.h"
#include "Input/Input.h"
#include "Lights/LightType.h"

const std::string DEFAULT_MAT_NAME = "default";

namespace FlyEngine
{

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

		isRunning = false;
		directionalLight = CreateDirectionalLight();
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

	void BaseGame::CreateBuffers(Buffer* buffers)
	{
		renderer->CreateBaseBuffers(*buffers);
	}

	void BaseGame::BindBuffers(Buffer* buffers, std::vector<float> vertex, std::vector<unsigned int> index)
	{
		renderer->BindBuffers(*buffers, vertex, vertex.size(), index, index.size());
	}

	void BaseGame::SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes)
	{
		renderer->SetVertexAttributes(vertexAttributes);
	}

	void BaseGame::DrawObjects()
	{
		renderer->UseDefaultShader();
		CalculateLights();
		DrawEntities();
		renderer->UseModelShader();
		DrawModels();
	}

	void BaseGame::DrawModels()
	{
		for (Entities::Model* model : modelList)
		{
			if (model->IsActive())
			{
				SetMatrixUniforms(model->GetModelMatrix());
				renderer->DrawModel(model);
			}
		}
	}

	void BaseGame::DrawEntities()
	{
		for (Entities::Entity* entity : entityList)
		{
			if (entity->IsActive())
			{
				SetMatrixUniforms(entity->GetModelMatrix());
				
				SetMaterialUniforms(entity);
				renderer->SetVec3Uniform("baseColor", entity->GetColor().GetColorV3());
				
				renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
			}
		}
	}


	void BaseGame::CalculateLights()
	{
		int pointLightIndex = 0;
		for (Lights::Light* light : lightList)
		{
			if (pointLightIndex < 4)//Cambiar por una constante
			{
				SetLightUniforms(light, pointLightIndex);
				if (light->GetLightType() == Lights::LightType::Point)
					pointLightIndex++;
			}
		}
	}

	void BaseGame::SetMatrixUniforms(glm::mat4 entityMatrix)
	{
		renderer->SetMatrix4Uniform("view", mainCamera->GetViewMatrix());
		renderer->SetMatrix4Uniform("projection", mainCamera->GetProjMatrix());
		renderer->SetMatrix4Uniform("model", entityMatrix);
		renderer->SetVec3Uniform("viewPos", mainCamera->GetPosition());
	}

	void BaseGame::SetLightUniforms(Lights::Light* light, int index)
	{
		switch (light->GetLightType())
		{
		case Lights::LightType::Directional:
			renderer->SetDirectionalLight((Lights::DirectionalLight*)light);
			break;
		case Lights::LightType::Point:
			renderer->SetPointLight((Lights::PointLight*)light, index);
			break;
		case Lights::LightType::Spot:
			renderer->SetSpotLight((Lights::SpotLight*)light);
			break;
		default:
			break;
		}
		renderer->SetVec3Uniform("lightColor", light->GetColor().GetColorV3()); 
	}

	void BaseGame::SetMaterialUniforms(Entities::Entity* entity)
	{
		Materials::Material* mat = entity->GetMaterial();

		mat->ApplyTextures();
		renderer->SetIntUniform("material.diffuse", 0);
		renderer->SetIntUniform("material.specular", 1);
		renderer->SetFloatUniform("material.shininess", 64);
	}

	float BaseGame::PixelsToEngine(int objectWidthInPixels, float windowDimension)
	{
		return (objectWidthInPixels * 1.0f) / windowDimension;
	}

	void BaseGame::CreateDefaultMaterial()
	{
		Materials::Material* commonMat = CreateMaterial(DEFAULT_MAT_NAME);
		commonMat->AddTexture("diffuse", Importers::TextureImporter::LoadTexture("res\\Textures\\White.png", true));
		commonMat->AddTexture("specular", Importers::TextureImporter::LoadTexture("res\\Textures\\White.png", true));

		std::vector<std::string> textureOrder = { "diffuse", "specular" };
		commonMat->SetTextureOrder(textureOrder);
	}

	Entities::Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width, float height)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Entities::Rectangle* rec = new Entities::Rectangle();
		rec->SetPosition(PixelsToEngine(posX, windowSize.x), PixelsToEngine(posY, windowSize.x), PixelsToEngine(posZ, windowSize.x));
		rec->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(height, windowSize.x), 1);

		rec->SetMaterial(materialsMap[DEFAULT_MAT_NAME]);

		CreateBuffers(rec->GetBuffers());
		BindBuffers(rec->GetBuffers(), rec->GetVertexList(), rec->GetIndexList());
		SetVertexAttributes(rec->GetVertexAttributes());
		entityList.push_back(rec);
		return rec;
	}

	Entities::Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width)
	{
		return CreateRectangle(posX, posY, posZ, width, width);
	}

	Entities::Triangle* BaseGame::CreateTriangle(float posX, float posY, float posZ, float base, float height)
	{
		Entities::Triangle* tri = new Entities::Triangle();

		tri->SetMaterial(materialsMap[DEFAULT_MAT_NAME]);

		return tri;
	}

	Entities::Cube* BaseGame::CreateCube(float posX, float posY, float posZ, float width)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Entities::Cube* cube = new Entities::Cube();
		cube->SetPosition(posX, posY, posZ);
		cube->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x));

		cube->SetMaterial(materialsMap[DEFAULT_MAT_NAME]);

		CreateBuffers(cube->GetBuffers());
		BindBuffers(cube->GetBuffers(), cube->GetVertexList(), cube->GetIndexList());
		SetVertexAttributes(cube->GetVertexAttributes());
		entityList.push_back(cube);
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

	void BaseGame::InternalInit()
	{
		Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
		//Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
		//std::cin.get();

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
		
		CreateDefaultMaterial();

		Init();
	}

	void BaseGame::InternalUpdate()
	{
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
			Input::Update();

			InternalUpdate();
			InternalDraw();
			glfwPollEvents();
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
		CameraController* cc = new CameraController(controllingCamera, window);
		cc->SetMode(cameraMode);
		cc->SetObjetiveParameters(new ObjetiveParams(target, followDistance));

		std::string text = "CameraController Created!";
		Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);

		return cc;
	}

	Materials::Material* BaseGame::CreateMaterial(std::string name)
	{
		Materials::Material* mat = new Materials::Material(name);
		materialsMap[name] = mat;
		std::string text = "Material Created: [" + name + "]!";
		Utils::Debugger::ConsoleMessage(&text[0],1,0,1,1);
		return mat;
	}

	Entities::Model* BaseGame::CreateModel(std::string const& path, std::string name)
	{
		Entities::Model* model = Importers::ModelImporter::LoadModel(path);
		model->SetName(name);
		std::string text = "Model Loaded: (" + model->GetName() + ")!";
		Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);
		modelList.push_back(model);
		return model;
	}

}
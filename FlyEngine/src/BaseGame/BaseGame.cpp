#include "BaseGame.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#include "Renderer/Renderer.h"

#include "TextureImporter/TextureImporter.h"

#include "Material/Material.h"
#include "FlyFunctions/Debugger/Debugger.h"
#include "FlyFunctions/Commons/Commons.h"
#include "FlyFunctions/ColorCode/ColorCode.h"
#include "MaterialSpecification/MaterialSpecification.h"
#include "Input/Input.h"
#include "Lights/LightType.h"

namespace FlyEngine
{
	//using namespace Entities;


	void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
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
		directionalLight = new Lights::DirectionalLight
		(
			glm::vec3(0, -1, 0),
			glm::vec3(1.00f, 1.00f, 1.0f),
			glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.4f, 0.4f, 0.4f)
		);
		lightList.push_back(directionalLight);
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

	void ResizeViewport(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
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
		//for (Lights::Light* light : lightList)

		DrawEntities();
	}

	void BaseGame::DrawEntities()
	{

		CalculateLights();

		for (Entities::Entity* entity : entityList)
		{
			if (entity->IsActive())
			{

				SetMatrixUniforms(entity->GetModelMatrix());
				//SetLightUniforms();
				SetMaterialUniforms(entity);
				//Esta linea es por si se quiere poner un efecto de color general a todo lo renderizado del engine
				//No es una luz, es un filtro
				renderer->SetVec3Uniform("colorMultiplier", entity->GetColor().GetColorV3());

				renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());

			}
		}
		//renderer->SetNewShader();
		//renderer->DrawObject();
	}

	/*
	void BaseGame::DrawTextures()
	{
		for (Texture* texture : textureList)
		{
			if (texture->IsActive())
			{
				int shader = entity->GetMaterial()->GetShaderID();

				entity->ApplyMaterial();

				SetMatrixUniforms(shader, entity->GetModelMatrix());
				SetLightUniforms(shader);
				SetMaterialUniforms(shader, entity);

				//Esta linea es por si se quiere poner un efecto de color general a todo lo renderizado del engine
				//No es una luz, es un filtro
				renderer->SetVec3Uniform(shader, "colorMultiplier", entity->GetColor().GetColorV3());

				renderer->DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
				int a;
			}
		}
	}*/

	void BaseGame::CalculateLights()
	{
		int pointLightIndex = 0;
		for (Lights::Light* light : lightList)
		{
			SetLightUniforms(light, pointLightIndex);
			if (light->GetLightType() == Lights::LightType::Point)
				pointLightIndex++;
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
	}

	void BaseGame::SetMaterialUniforms(Entities::Entity* entity)
	{
		Materials::MaterialSpecification* mat = entity->GetMaterial()->GetSpecs();

		//renderer->SetVec3Uniform("material.ambient", mat->GetAmbient());
		//renderer->SetVec3Uniform("material.diffuse", mat->GetDiffuse());
		//renderer->SetVec3Uniform("material.specular", mat->GetSpecular());
		renderer->SetFloatUniform("material.shininess", mat->GetShininess());
	}

	float BaseGame::PixelsToEngine(int objectWidthInPixels, float windowDimension)
	{
		return (objectWidthInPixels * 1.0f) / windowDimension;
	}

	Entities::Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width, float height)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Entities::Rectangle* rec = new Entities::Rectangle();
		rec->SetPosition(posX, posY, posZ);
		//rec->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(height, windowSize.y), 1);
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
		return tri;
	}

	Entities::Cube* BaseGame::CreateCube(float posX, float posY, float posZ, float width)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Entities::Cube* cube = new Entities::Cube();
		cube->SetPosition(posX, posY, posZ);
		cube->SetScale(PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x), PixelsToEngine(width, windowSize.x));
		CreateBuffers(cube->GetBuffers());
		BindBuffers(cube->GetBuffers(), cube->GetVertexList(), cube->GetIndexList());
		SetVertexAttributes(cube->GetVertexAttributes());
		entityList.push_back(cube);
		return cube;
	}

	void BaseGame::SetLight(Entities::Entity* newLight)
	{
		//light = newLight;
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
			Debugger::ConsoleMessage("GLFW Loaded Successfully", 2, 0, 1, 1);
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
		glfwMakeContextCurrent(window->GetWindow());
		glfwSetFramebufferSizeCallback(window->GetWindow(), frameBufferResizeCallback);

		//mainCamera = new Camera(FlyEngine::ProjectionType::Perspective, 60.0f, initialWindowWidth / initialWindowHeight, 0.1f, 500.0f);
		mainCamera = new Camera();

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

		Input::SetContextWindow(window);

		glfwSetFramebufferSizeCallback(window->GetWindow(), ResizeViewport);

		renderer = new Renderer();


		Init();
	}

	void BaseGame::InternalUpdate()
	{
		renderer->SetBackgroundColor(Color::GetColor(FlyEngine::COLOR::MOSS_GREEN));
		if (checkEsc)
		{
			if (Input::GetKeyDown(KeyCode::KEY_ESCAPE))
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
		return Importers::TextureImporter::LoadTexture(path);
	}

}
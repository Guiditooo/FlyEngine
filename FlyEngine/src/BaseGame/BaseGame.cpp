#include "BaseGame.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"

#include "FlyFunctions/Debugger/Debugger.h"
#include "FlyFunctions/Commons/Commons.h"
#include "FlyFunctions/ColorCode/ColorCode.h"
#include "Input/Input.h"
#include "string"

namespace FlyEngine
{
	using namespace Entities;
	Input innerInputSystem;

	BaseGame::BaseGame()
	{
		window = nullptr;
		mainCamera = nullptr;

		initialWindowName = "FlyEngine";
		initialWindowWidth = 0;
		initialWindowHeight = 0;
		checkEsc = true;

		isRunning = false;
	}

	BaseGame::~BaseGame()
	{
		if (mainCamera != nullptr)
			delete mainCamera;
		mainCamera = nullptr;
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
		renderer.CreateBaseBuffers(*buffers);
	}

	void BaseGame::BindBuffers(Buffer* buffers, std::vector<float> vertex, std::vector<unsigned int> index)
	{
		renderer.BindBuffers(*buffers, vertex, vertex.size(), index, index.size());
	}

	void BaseGame::SetVertexAttributes(std::vector<VertexAttribute> vertexAttributes)
	{
		renderer.SetVertexAttributes(vertexAttributes);
	}

	void BaseGame::DrawObjects()
	{
		//for (Lights::Light* light : lightList)

		for (Entities::Entity* entity : entityList)
		{
			if (entity->IsActive())
			{
				entity->ApplyMaterial();
				
				renderer.SetMatrixUniform(entity->GetMaterial()->GetShaderID(), "viewMatrix", mainCamera->GetViewMatrix());
				renderer.SetMatrixUniform(entity->GetMaterial()->GetShaderID(), "projectionMatrix", mainCamera->GetProjMatrix());
				renderer.SetMatrixUniform(entity->GetMaterial()->GetShaderID(), "modelMatrix", entity->GetModelMatrix());

				//Esta linea es por si se quiere poner un efecto de color general a todo lo renderizado del engine
				//No es una luz, es un filtro
				renderer.SetVec3Uniform(entity->GetMaterial()->GetShaderID(), "colorMultiplier", entity->GetColor().GetColorV3());
				
				renderer.SetVec3Uniform(entity->GetMaterial()->GetShaderID(), "lightColor", glm::vec3(1.0f,1.0f,1.0f));
				renderer.SetVec3Uniform(entity->GetMaterial()->GetShaderID(), "lightPos", light->GetPosition());
				
				renderer.SetVec3Uniform(entity->GetMaterial()->GetShaderID(), "viewPos", mainCamera->GetPosition());
				


				renderer.DrawRequest(*(entity->GetBuffers()), entity->GetIndexCount());
			}
		}
	}
	
	float BaseGame::PixelsToEngine(int objectWidthInPixels, float windowDimension)
	{
		return (objectWidthInPixels * 1.0f) / windowDimension;
	}

	Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ,float width, float height)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Rectangle* rec = new Rectangle();
		rec->SetPosition(posX, posY, posZ);
		rec->SetScale(PixelsToEngine(width,windowSize.x), PixelsToEngine(height, windowSize.y), 1);
		CreateBuffers(rec->GetBuffers());
		BindBuffers(rec->GetBuffers(), rec->GetVertexList(), rec->GetIndexList());
		SetVertexAttributes(rec->GetVertexAttributes());
		entityList.push_back(rec);
		return rec;
	}

	Rectangle* BaseGame::CreateRectangle(float posX, float posY, float posZ, float width)
	{
		return CreateRectangle(posX,posY,posZ,width,width);
	}
	
	Triangle* BaseGame::CreateTriangle(float posX, float posY, float posZ, float base, float height)
	{
		Triangle* tri = new Triangle();
		return tri;
	}

	Cube* BaseGame::CreateCube(float posX, float posY, float posZ, float width)
	{
		glm::vec2 windowSize = window->GetWindowSize();
		Cube* cube = new Cube();
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
		light = newLight;
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

		//mainCamera = new Camera(FlyEngine::ProjectionType::Perspective, 60.0f, initialWindowWidth / initialWindowHeight, 0.1f, 500.0f);
		mainCamera = new Camera(glm::vec3(0,0,-5));
		
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

		innerInputSystem = Input(window);

		glfwSetFramebufferSizeCallback(window->GetWindow(), ResizeViewport);

		Init();
	}

	void BaseGame::InternalUpdate()
	{
		if (checkEsc)
		{
			if (innerInputSystem.GetKeyDown(KeyCode::KEY_ESCAPE))
			{
				glfwSetWindowShouldClose((window->GetWindow()), true);
			}
		}
		Update();
	}

	void BaseGame::InternalDraw()
	{
		renderer.SetBackgroundColor(Color::GetColor(FlyEngine::COLOR::FLYBLACK));

		DrawObjects();

		SwapBuffers();
	}

	void BaseGame::InternalDeinit()
	{
		Deinit();

		glfwTerminate();

		FlyEngine::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
		//FlyEngine::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
		//std::cin.get();
		//system("cls");

		delete window;
	}

	void BaseGame::SwapBuffers()
	{
		glfwSwapBuffers(window->GetWindow());
	}

	void BaseGame::RunGame()
	{
		isRunning = true;
		InternalInit();

		//Tengo que hacer una funcion que me resizee el objeto en pixeles, como raylib.
		/*
			Necesito el tamaño de la ventana
			Necesito el tamaño en pixeles de lo que quiero depositar
			Necesito un tamaño base del objeto el cual presettear en el constructor

			tamaño de 1 pixel * tamaño del objeto en pixeles = tamaño fixeado del objeto en pantalla
			widthInWindow = 1/windowWidth * modelWidth
			heightInWindow = 1/windowHeight * modelHeight


			Donde pongo esto?
		*/

		while (isRunning && !glfwWindowShouldClose(window->GetWindow()))
		{
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

}
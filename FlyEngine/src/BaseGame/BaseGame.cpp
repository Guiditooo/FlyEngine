#include "BaseGame.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <Window/Window.h>

#include <Renderer/Renderer.h>

#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
#include <FlyFunctions/ColorCode/ColorCode.h>
#include <Input/Input.h>
#include <Shader/Shader.h>

#include <Triangle/Triangle.h>
#include <Rectangle/Rectangle.h>

namespace FlyEngine
{
	Input innerInputSystem;

	BaseGame::BaseGame()
	{
		isRunning = false;
		window = nullptr;
		initialWindowName = "FlyEngine";
		initialWindowWidth = 0;
		initialWindowHeight = 0;
		checkEsc = true;
	}

	BaseGame::~BaseGame()
	{

	}

	void BaseGame::SetWindowParameters(int width, int height, std::string name)
	{
		initialWindowWidth = width;
		initialWindowHeight = height;
		initialWindowName = name;
	}

	void ResizeViewport(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void BaseGame::InternalInit()
	{
		Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
		Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
		std::cin.get();

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

		glewInit();

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
		Renderer::SetBackgroundColor(Color::GetColor(FlyEngine::COLOR::FLYBLACK));

		Renderer::DrawRenderizableObjects();

		SwapBuffers();
	}

	void BaseGame::InternalDeinit()
	{
		Deinit();

		glfwTerminate();

		FlyEngine::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
		FlyEngine::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
		std::cin.get();
		system("cls");

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
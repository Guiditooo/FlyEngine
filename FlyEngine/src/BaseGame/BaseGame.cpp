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

BaseGame::BaseGame()
{
	isRunning = false;
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

void BaseGame::InternalUpdate()
{
	if (checkEsc)
	{
		if (Input::GetKeyDown(KeyCode::KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window->GetWindow(), true);
		}
	}
	Update();
}

void BaseGame::InternalDraw()
{	
	Renderer::SetBackgroundColor(Color::GetColor(FLY_ENGINE::COLOR::RAYBLACK));

	Renderer::DrawRenderizableObjects();

	SwapBuffers();
}

void BaseGame::InternalDeinit()
{
	Deinit();

	glfwTerminate();

	FLY_ENGINE::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
	FLY_ENGINE::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
	//std::cin.get();
	system("cls");

	delete window;
}

void BaseGame::SwapBuffers()
{
	glfwSwapBuffers(window->GetWindow());
}

void BaseGame::InternalInit()
{
	Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
	Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
	//std::cin.get();
	//system("cls");

	glfwInit();

	if (initialWindowHeight < 0 || initialWindowWidth < 0)
	{
		window = new Window(initialWindowName);
	}
	else
	{
		window = new Window(initialWindowWidth, initialWindowHeight, initialWindowName);
	}
	glfwMakeContextCurrent(window->GetWindow());

	glewInit();

	Input::SetContextWindow(window);
	glfwSetFramebufferSizeCallback(window->GetWindow(), ResizeViewport);

	Init();
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
	
	Rectangle* test1 = new Rectangle();
	Triangle* test2 = new Triangle();

	test1->SetColor(FLY_ENGINE::COLOR::CYAN);
	test2->SetColor(FLY_ENGINE::COLOR::YELLOW);
	test1->SetDrawLayer(1);
	//test1->Rotate(0, 0, 45);

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

#include "BaseGame.h"

#include <Renderer/Renderer.h>

#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
#include <FlyFunctions/ColorCode/ColorCode.h>
#include <Input/Input.h>
#include <Shader/Shader.h>

//#include <Shape/Shape.h>
#include <Triangle/Triangle.h>
#include <Rectangle/Rectangle.h>

bool BaseGame::isRunning = false;
Window* BaseGame::window = nullptr;

using namespace FLY_ENGINE;

BaseGame::BaseGame()
{
	isRunning = false;
}

BaseGame::~BaseGame()
{

}

void BaseGame::ResizeViewport(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void BaseGame::Init()
{
	Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
	Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
	//std::cin.get();
	//system("cls");

	glfwInit();

	window = new Window("Fly Engine");
	glfwMakeContextCurrent(window->GetWindow());

	glewInit();

	Input::SetContextWindow(window);
	glfwSetFramebufferSizeCallback(window->GetWindow(), ResizeViewport);
}

void BaseGame::Update()
{
	if (Input::GetKeyDown(KeyCode::KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window->GetWindow(), true);
	}
}

void BaseGame::Draw()
{	
	Renderer::SetBackgroundColor(Color::GetColor(FLY_ENGINE::COLOR::RAYBLACK));

	Renderer::DrawRenderizableObjects();

	SwapBuffers();
}

void BaseGame::Deinit()
{
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

void BaseGame::RunGame()
{
	isRunning = true;
	Init();

	//FLY_ENGINE::Debugger::ConsoleMessage("Type of isRunning: ", 2, 0, 2, 0);
	//FLY_ENGINE::Debugger::ConsoleMessage(typeid(isRunning).name(), 0, 0, 0, 2);

	//Shader* test = new Shader("C:\\Users\\usuario\\source\\repos\\FlyEngine\\FlyEngine\\res\\Shaders\\fragment.shader", "C:\\Users\\usuario\\source\\repos\\FlyEngine\\FlyEngine\\res\\Shaders\\vertex.shader");
	Rectangle* test1 = new Rectangle();
	//Triangle* test2 = new Triangle();
	//Rectangle* test3 = new Rectangle();

	Material* rectangleMat = new Material();
	test1->SetMaterial(rectangleMat);

	
	//FLY_ENGINE::Debugger::ConsoleMessage(&(test->UseShader())[0], 2, 0, 2, 0);




	while (isRunning && !glfwWindowShouldClose(window->GetWindow()))
	{
		Update();
		Draw();
		glfwPollEvents();
	}

	Deinit();
}

bool BaseGame::IsGameRunning()
{
	return isRunning;
}



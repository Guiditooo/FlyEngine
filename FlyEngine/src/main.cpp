#include <GLEW/glew.h>
#include <FlyFunctions/Debugger/Debugger.h>
#include <FlyFunctions/Commons/Commons.h>
#include <Window/Window.h>
#include <Input/Input.h>

using namespace std;

int main() 
{
    glfwInit();
    FLY_ENGINE::Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
    FLY_ENGINE::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
    std::cin.get();
    system("cls");

    Window* window = new Window(800, 600, "Fly Engine");
    
    glfwMakeContextCurrent(window->GetWindow());

    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        if (Input::GetKeyDown(window->GetWindow(), FLY_ENGINE::KeyCode::KEY_ESCAPE))
            glfwSetWindowShouldClose(window->GetWindow(),true);        

        glClearColor(FLY_ENGINE::Commons::RandomFloat(0.0f,1.0f), FLY_ENGINE::Commons::RandomFloat(0.0f, 1.0f), FLY_ENGINE::Commons::RandomFloat(0.0f, 1.0f), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window->GetWindow());
    }

    glfwTerminate();

    FLY_ENGINE::Debugger::ConsoleMessage("Ending Fly Engine.", 2, 0, 1, 0);
    FLY_ENGINE::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
    std::cin.get();
    system("cls");

    delete window;

    return 0;
}


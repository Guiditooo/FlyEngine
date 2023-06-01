#include <GLEW/glew.h>
#include <FlyFunctions/Debugger/Debugger.h>
#include <Input/Input.h>
#include <Window/Window.h>

#include <string>

using namespace std;


int main() 
{
    glfwInit();
    Window* window = new Window(800, 600, "Fly Engine");
    //FLY_ENGINE::Debugger::ConsoleMessage("Starting Fly Engine.", 2, 0, 1, 0);
    //FLY_ENGINE::Debugger::ConsoleMessage("Press intro to continue.", 2, 0, 1, 0);
    glfwMakeContextCurrent(window->GetWindow());

    while (!glfwWindowShouldClose(window->GetWindow()))
    {
        if (Input::GetKeyDown(window->GetWindow(), FLY_ENGINE::KeyCode::KEY_ESCAPE))
            glfwSetWindowShouldClose(window->GetWindow(),true);

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window->GetWindow());
    }

    glfwTerminate();

    delete window;

    return 0;
}


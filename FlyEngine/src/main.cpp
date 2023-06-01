#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <FlyFunctions/Debugger/Debugger.h>

using namespace std;

int main() {
    
    glfwInit();
    FLY_ENGINE::Debugger::ConsoleMessage("Starting Fly Engine. Press intro to continue.", 2, 0, 1);
    cin.get();
    system("cls");

    return 0;
}


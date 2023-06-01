#include <iostream>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

int main() {
    // Inicializar GLFW
    glfwInit();

    cout << endl << "Opening Fly Engine" << endl << endl;
    cin.get();
    system("cls");
    // Crear una ventana GLFW

    // Inicializar GLEW
    glewExperimental = GL_TRUE; // Activar el modo experimental para todas las extensiones
    glewInit();

    // Comprobar si GLEW se inicializó correctamente
    if (glewInit() != GLEW_OK) {
        // Ocurrió un error al inicializar GLEW
        // Manejar el error...
        return -1;
    }

    // Ahora puedes utilizar las funciones y extensiones de OpenGL cargadas por GLEW

    // Terminar GLFW
    glfwTerminate();

    return 0;
}


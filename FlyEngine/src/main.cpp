#include <stb_include.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "TinyXML2/tinyxml2.h"

/*

#include <glew.h>
#include <glfw3.h>

int main() {
    // Inicializar GLFW
    glfwInit();

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
*/

/*#include <iostream>
void main()
{
    std::cout << "Hola";
}
*/



#include <glfw3.h>

using namespace tinyxml2;
using namespace std;

int main(void)
{
    GLFWwindow* window;
    XMLDocument doc;

    string test = doc.LoadFile("") == XML_SUCCESS ? "Exists" : "Does not exist";

    cout << endl << test;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current 
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        // Render here 
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers 
        glfwSwapBuffers(window);

        //Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


/*
#include <glm/vec2.hpp>           // vec2
#include <glm/vec3.hpp>           // vec3
#include <glm/mat4x4.hpp>         // mat4
#include <glm/trigonometric.hpp>  //radians

// Include GLM extension
#include <glm/ext/matrix_transform.hpp> // perspective
#include <glm/ext/matrix_clip_space.hpp> // translate, rotate

glm::mat4 transform(glm::vec2 const& Orientation, glm::vec3 const& Translate, glm::vec3 const& Up)
{
    glm::mat4 Proj = glm::perspective(glm::radians(45.f), 1.33f, 0.1f, 10.f);
    glm::mat4 ViewTranslate = glm::translate(glm::mat4(1.f), Translate);
    glm::mat4 ViewRotateX = glm::rotate(ViewTranslate, Orientation.y, Up);
    glm::mat4 View = glm::rotate(ViewRotateX, Orientation.x, Up);
    glm::mat4 Model = glm::mat4(1.0f);
    return Proj * View * Model;
}
*/

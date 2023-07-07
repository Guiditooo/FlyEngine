#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

std::string GetFileText(const char* path)
{
    std::ifstream inputFile(path);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return "ERROR";
    }

    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    std::string fileContent = buffer.str(); 

    inputFile.close();//Importante cerrar esto antes de terminar la funcion
    return fileContent;
}

Shader::Shader(const char* fragmentShaderPath, const char* vertexShaderPath)
{
    std::string vertexSource = GetFileText(vertexShaderPath);
    std::string fragmentSource = GetFileText(fragmentShaderPath);

	const char* vertexText = vertexSource.c_str();
    const char* fragmentText = fragmentSource.c_str();
    
    unsigned int vertexID;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexText, NULL);
    glCompileShader(vertexID);
    CheckCompileErrors(vertexID, "VERTEX");

    unsigned int fragmentID;
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentText, NULL);
    glCompileShader(fragmentID);
    CheckCompileErrors(fragmentID, "FRAGMENT");

    id = glCreateProgram();
    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);

    glLinkProgram(id);
    CheckCompileErrors(id, "PROGRAM");

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

Shader::~Shader()
{
}

void Shader::UseShader()
{
    glUseProgram(id);
}

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
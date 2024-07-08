#include "Shader.h"
#include <fstream>
#include <sstream>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace FlyEngine
{

	std::string GetFileText(const char* path)
	{
		std::ifstream inputFile(path);//Constructor que insta abre el archivo del path
		if (!inputFile.is_open())
		{
			std::string errorText = "Failed to open the file at: ";
			errorText += path;
			return errorText;
		}

		std::stringstream buffer;
		buffer << inputFile.rdbuf(); //Contenido del archivo plano

		std::string fileContent = buffer.str(); //Contenido del archivo en string

		inputFile.close();//Importante cerrar esto antes de terminar la funcion
		return fileContent;
	}

	Shader::Shader(const char* fragmentShaderPath, const char* vertexShaderPath, std::string shaderName, const char* geometryShaderPath)
	{
		std::string vertexSource = GetFileText(vertexShaderPath);
		std::string fragmentSource = GetFileText(fragmentShaderPath);
		std::string geometrySource;

		const char* vertexText = vertexSource.c_str();
		const char* fragmentText = fragmentSource.c_str();
		

		GLuint vertexID;
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vertexText, NULL);
		glCompileShader(vertexID);
		CheckCompileErrors(vertexID, "VERTEX", shaderName);

		unsigned int fragmentID;
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &fragmentText, NULL);
		glCompileShader(fragmentID);
		CheckCompileErrors(fragmentID, "FRAGMENT", shaderName);

		unsigned int geometryID;
		if (geometryShaderPath != nullptr)
		{
			geometrySource = GetFileText(geometryShaderPath);
			const char* geometryText = geometrySource.c_str();
			geometryID = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryID, 1, &geometryText, NULL);
			glCompileShader(geometryID);
			CheckCompileErrors(geometryID, "GEOMETRY", shaderName);
		}

		id = glCreateProgram();
		glAttachShader(id, vertexID);
		glAttachShader(id, fragmentID);
		if (geometryShaderPath != nullptr)
			glAttachShader(id, geometryID);

		glLinkProgram(id);
		CheckCompileErrors(id, "PROGRAM", shaderName);

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		if (geometryShaderPath != nullptr)
			glDeleteShader(geometryID);
	}

	Shader::~Shader()
	{
	}

	unsigned int Shader::GetShaderID()
	{
		return id;
	}

	void Shader::UseShader()
	{
		glUseProgram(id);
	}

	void Shader::CheckCompileErrors(unsigned int shader, std::string type, std::string shaderName)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (success)
			{
				std::cout << "SUCCESS on loading " << type << " of " << shaderName << "\n" << "---------------------------------------------------- - -- " << std::endl;
			}
			else
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << " of " << shaderName << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (success)
			{
				if (success)
				{
					std::cout << "SUCCESS CREATING PROGRAM of " << shaderName <<"\n" << "---------------------------------------------------- - -- " << std::endl;
				}
			}
			else
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << " of " << shaderName << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}
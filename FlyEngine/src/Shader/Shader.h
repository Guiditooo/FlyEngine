#ifndef SHADER_H
#define SHADER_H

#include <Exports/Exports.h>
#include <iostream>

namespace FlyEngine
{

	class FLY_API Shader
	{
	private:
		unsigned int id;
		std::string name;
		void CheckCompileErrors(unsigned int shader, std::string type, std::string shaderName);
	public:
		Shader(std::string shaderName, const char* fragmentShaderPath, const char* vertexShaderPath, const char* geometryPath = nullptr/* = "SomeShader"*/);
		~Shader();

		unsigned int GetShaderID();
		std::string GetShaderName();

		void UseShader();
	};

}
#endif // !SHADER_H
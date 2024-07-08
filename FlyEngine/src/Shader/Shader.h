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
		void CheckCompileErrors(unsigned int shader, std::string type, std::string shaderName);
	public:
		Shader(const char* fragmentShaderPath, const char* vertexShaderPath, std::string shaderName, const char* geometryPath = nullptr/* = "SomeShader"*/);
		~Shader();

		unsigned int GetShaderID();

		void UseShader();
	};

}
#endif // !SHADER_H
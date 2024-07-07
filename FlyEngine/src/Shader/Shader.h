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
		void CheckCompileErrors(unsigned int shader, std::string type);
	public:
		Shader(const char* fragmentShaderPath, const char* vertexShaderPath, const char* geometryPath = nullptr);
		~Shader();

		unsigned int GetShaderID();

		void UseShader();
	};

}
#endif // !SHADER_H
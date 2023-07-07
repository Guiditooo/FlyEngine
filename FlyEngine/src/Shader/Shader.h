#ifndef SHADER_H
#define SHADER_H

#include <Exports/Exports.h>
#include <iostream>

class Shader
{
private:
	int id;
	void CheckCompileErrors(unsigned int shader, std::string type);
public:
	Shader(const char* fragmentShaderPath, const char* vertexShaderPath);
	~Shader();

	void UseShader();
};

#endif // !SHADER_H

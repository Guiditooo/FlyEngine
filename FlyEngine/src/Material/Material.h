#ifndef MATERIAL_H
#define MATERIAL_H

#include <Exports/Exports.h>
#include <Shader/Shader.h>
#include <glm/glm.hpp>

class FLY_API Material
{
private:
	Shader* shader;
public:
	Material();
	Material(const char* fragmentShaderPath, const char* vertexShaderPath);
	~Material();

	int GetShaderID();
	void Apply();
};



#endif // !MATERIAL_H

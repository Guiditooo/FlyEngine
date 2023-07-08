#include "Material.h"

const char* DEFAULT_VERTEX_PATH = "res/Shaders/vertex.shader";
const char* DEFAULT_FRAGMENT_PATH = "res/Shaders/fragment.shader";

Material::Material()
{
	shader = new Shader(DEFAULT_FRAGMENT_PATH, DEFAULT_VERTEX_PATH);
}

Material::Material(const char* fragmentShaderPath, const char* vertexShaderPath)
{
	shader = new Shader(fragmentShaderPath, vertexShaderPath);
}

Material::~Material()
{

}

int Material::GetShaderID()
{
	return shader->GetShaderID();
}

void Material::Apply()
{
	shader->UseShader();
}

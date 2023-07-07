#include "Material.h"

const char* DEFAULT_VERTEX_PATH = "C:/Users/usuario/source/repos/FlyEngine/FlyEngine/res/Shaders/vertex.shader";
const char* DEFAULT_FRAGMENT_PATH = "C:/Users/usuario/source/repos/FlyEngine/FlyEngine/res/Shaders/fragment.shader";

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

void Material::Apply()
{
	shader->UseShader();
}

#include "Material.h"

const char* DEFAULT_VERTEX_PATH = "res/Shaders/vertex.shader";
const char* DEFAULT_FRAGMENT_PATH = "res/Shaders/fragment.shader";

namespace FlyEngine
{
	namespace Materials
	{

		Material::Material()
		{
			shader = new Shader(DEFAULT_FRAGMENT_PATH, DEFAULT_VERTEX_PATH);
			specs = new MaterialSpecification();
			specs->SetSpecs(MaterialList::WhitePlastic);
		}

		Material::Material(const char* fragmentShaderPath, const char* vertexShaderPath)
		{
			shader = new Shader(fragmentShaderPath, vertexShaderPath);
			specs = new MaterialSpecification();
			specs->SetSpecs(MaterialList::WhitePlastic);
		}

		Material::~Material()
		{

		}

		int Material::GetShaderID()
		{
			return shader->GetShaderID();
		}

		MaterialSpecification* Material::GetSpecs()
		{
			return specs;
		}


		void Material::Apply()
		{
			shader->UseShader();
		}
	}

}
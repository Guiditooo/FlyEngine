#include "Material.h"

#include "ShaderManager/ShaderManager.h"

#include "Shader/Shader.h"

namespace FlyEngine
{
	namespace Materials
	{

		Material::Material(std::string name, Shader* shader)
		{
			specs = new MaterialSpecification();
			specs->SetSpecs(MaterialList::WhitePlastic);
			this->name = name;

			this->shader = shader == nullptr ? Managers::ShaderManager::GetDefaultShader() : shader;
		}

		Material::~Material()
		{
			if (specs != nullptr)
			{
				delete specs;
				specs = nullptr;
			}

			for (auto& pair : textureMap)
			{
				std::cout << "\nUnloaded " << pair.first << " with ID=" << std::to_string(pair.second->GetID());
				delete pair.second;
			}
		}

		void Material::ApplyTextures()
		{
			for (int i = 0; i < textureOrder.size(); i++)
			{
				Texture* texture = GetTexture(textureOrder[i]);
				if (texture)
				{
					texture->Bind(i);
				}
			}
		}

		void Material::AddTexture(const std::string& name, Texture* texture)
		{
			if (textureMap.find(name) != textureMap.end())
			{
				std::cout << " Texture " << name << " already exists in [" << this->name << "] \n";
				return;
			}
			textureMap[name] = texture;

			std::cout << " Linked " << name << "(ID =" << std::to_string(texture->GetID()) << ") to [" << this->name << "] \n";

			if (std::find(textureOrder.begin(), textureOrder.end(), name) == textureOrder.end())
			{
				textureOrder.push_back(name);
			}
			texture->SetType(name);
		}

		void Material::SetTextureOrder(const std::vector<std::string>& order)
		{
			textureOrder = order;
		}

		void Material::SetSpecs(MaterialSpecification* newSpecs)
		{
			specs = newSpecs;
		}

		void Material::SetColor(Utils::Color newColor)
		{
			color = newColor;
		}

		void Material::SetColor(glm::vec3 newColor)
		{
			color = Utils::Color(newColor);
		}

		void Material::SetColor(glm::vec4 newColor)
		{
			color = Utils::Color(newColor);
		}

		void Material::SetColor(float r, float g, float b)
		{
			color = Utils::Color(r, g, b);
		}

		void Material::SetColor(float r, float g, float b, float a)
		{
			color = Utils::Color(r, g, b, a);
		}

		std::vector<std::string> Material::GetTextureOrder()
		{
			return textureOrder;
		}

		Texture* Material::GetTexture(const std::string& name) const
		{
			auto it = textureMap.find(name);
			if (it != textureMap.end())
			{
				return it->second;
			}
			return nullptr;
		}

		MaterialSpecification* Material::GetSpecs()
		{
			return specs;
		}

		std::string Material::GetName()
		{
			return name;
		}
		Utils::Color Material::GetColor()
		{
			return color;
		}
		Shader* Material::GetShader()
		{
			return shader;
		}
		unsigned int Material::GetShaderID()
		{
			return shader->GetShaderID();
		}
	}

}
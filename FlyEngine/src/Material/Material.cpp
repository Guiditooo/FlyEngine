#include "Material.h"

#include "ShaderManager/ShaderManager.h"
#include "TextureManager/TextureManager.h"

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

			this->shader = shader;
		}

		Material::~Material()
		{
			if (specs != nullptr) 
			{
				delete specs;
				specs = nullptr;
			}
		}

		void Material::ApplyTextures()
		{
			for (int i = 0; i < textureOrder.size(); i++)
			{
				int textureID = GetTexture(textureOrder[i]);
				
				if (textureID != -1)
				{
					Managers::TextureManager::BindTexture(textureID, i);
				}
			}
		}

		bool Material::AddTexture(const std::string& name, int textureID)
		{
			/*if (textureMap.find(name) != textureMap.end())
			{
				std::cout << " Texture " << name << " already exists in [" << this->name << "] \n";
				return false;
			}
			if (texture == nullptr)
			{
				std::cout << "Texture" << name << "not found!\n";
				return false;
			}
			*/

			textureMap[name] = textureID;

			std::cout << " Linked " << name << "(ID =" << std::to_string(textureID) << ") to [" << this->name << "] \n";

			if (std::find(textureOrder.begin(), textureOrder.end(), name) == textureOrder.end())
			{
				textureOrder.push_back(name);
			}
			
			Managers::TextureManager::SetTextureType(textureID, name);
			
			return true;
		}

		void Material::SetTextureOrder(const std::vector<std::string>& order)
		{
			textureOrder = order;
		}

		void Material::SetSpecs(MaterialSpecification* newSpecs)
		{
			specs = newSpecs;
		}

		void Material::SetSpecs(MaterialList material)
		{
			specs->SetSpecs(material);
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

		const std::unordered_map<std::string, int>& Material::GetTextureMap() const
		{
			return textureMap;
		}

		std::vector<std::string> Material::GetTextureOrder()
		{
			return textureOrder;
		}

		int Material::GetTexture(const std::string& name) const
		{
			auto it = textureMap.find(name);
			if (it != textureMap.end())
			{
				return it->second;
			}
			return -1;
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
		glm::vec3 Material::GetColorV3()
		{
			return color.GetColorV3();
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
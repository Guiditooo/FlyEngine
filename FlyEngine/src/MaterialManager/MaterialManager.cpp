#include "MaterialManager.h"

#include "TextureManager/TextureManager.h"

#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	namespace Managers
	{
		using namespace FlyEngine::Materials;

		std::unordered_map<std::string, Materials::Material*> MaterialManager::materialsMap;

		void MaterialManager::InitializeManager()
		{
			CreateBasicMaterial();
			CreateModelMaterial();
			CreateMissingMaterial();
		}

		void MaterialManager::CreateMaterial(std::string materialName, Shader* shader)
		{
			if (GetMaterial(materialName) != nullptr)
				return;

			materialsMap[materialName] = new Materials::Material(materialName, shader);

			std::string text = "Material Created: [" + materialName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);
		}

		void MaterialManager::EraseMaterial(std::string materialName)
		{
			auto it = materialsMap.find(materialName);
			if (it != materialsMap.end())
			{
				if (it->second);
					delete it->second;
				it->second = nullptr;
			}
		}

		Materials::Material* MaterialManager::GetMaterial(std::string name)
		{
			auto it = materialsMap.find(name);
			if (it != materialsMap.end())
			{
				return it->second;
			}
			return nullptr;
		}

		void MaterialManager::SetMaterial(std::string matName, Materials::Material* mat)
		{
			materialsMap[matName] = mat;

			std::string text = "Edited Material: [" + matName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 0, 1);
		}

		Materials::Material* MaterialManager::GetDefaultModelMaterial()
		{
			return GetMaterial(DEFAULT_MODEL_MAT_NAME);
		}
		Materials::Material* MaterialManager::GetDefaultBasicMaterial()
		{
			return GetMaterial(DEFAULT_BASIC_MAT_NAME);
		}
		Materials::Material* MaterialManager::GetDefaultMissingMaterial()
		{
			return GetMaterial(DEFAULT_MISSING_MAT_NAME);
		}

		bool MaterialManager::AddTexture(std::string materialName, std::string textureName, int textureID)
		{
			if (textureID == -1)
			{
				std::cout << "Texture" << textureName << "not found!\n";
				return false;
			}
			
			if (materialsMap.find(materialName) != materialsMap.end())
			{
				//std::cout << " Texture " << name << " already exists in [" << this->name << "] \n";
				//return false;
				Material* mat = materialsMap[materialName];

				if (mat->GetTextureMap().find(textureName) != mat->GetTextureMap().end())
				{
					std::cout << " Texture " << textureName << " already exists in [" << mat->GetName() << "] \n";
					return false;
				}
				
				mat->AddTexture(textureName, textureID);

				return true;
			}
			else
			{
				std::cout << "Material " << materialName << " does not Exist!";
			}

			return false;
		}

		void MaterialManager::SetTextureOrder(const std::string& materialName, const std::vector<std::string>& order)
		{
			Material* mat = materialsMap[materialName]; 
			mat->SetTextureOrder(order);
		}

		void MaterialManager::CreateBasicMaterial()
		{
			CreateMaterial(DEFAULT_BASIC_MAT_NAME, ShaderManager::GetDefaultBasicShader());
			Materials::Material* defMat = GetMaterial(DEFAULT_BASIC_MAT_NAME);
			defMat->AddTexture("diffuse", TextureManager::GetDefaultTextureID());
			defMat->AddTexture("specular", TextureManager::GetDefaultTextureID());

			std::vector<std::string> textureOrder = { "diffuse", "specular" };
			defMat->SetTextureOrder(textureOrder);

			defMat->SetColor(Utils::Color(Utils::COLOR::WHITE));

			SetMaterial(DEFAULT_BASIC_MAT_NAME, defMat);
		}

		void MaterialManager::CreateModelMaterial()
		{
			CreateMaterial(DEFAULT_MODEL_MAT_NAME, ShaderManager::GetDefaultModelShader());
			Materials::Material* defMat = GetMaterial(DEFAULT_MODEL_MAT_NAME);
			defMat->AddTexture("diffuse", TextureManager::GetDefaultTextureID());
			defMat->AddTexture("specular", TextureManager::GetDefaultTextureID());

			std::vector<std::string> textureOrder = { "diffuse", "specular" };
			defMat->SetTextureOrder(textureOrder);

			defMat->SetColor(Utils::Color(Utils::COLOR::WHITE));

			SetMaterial(DEFAULT_MODEL_MAT_NAME, defMat);
		}

		void MaterialManager::CreateMissingMaterial()
		{
			CreateMaterial(DEFAULT_MISSING_MAT_NAME, ShaderManager::GetDefaultBasicShader());
			Materials::Material* defMat = GetMaterial(DEFAULT_MISSING_MAT_NAME);
			defMat->AddTexture("diffuse", TextureManager::GetDefaultTextureID());
			defMat->AddTexture("specular", TextureManager::GetDefaultTextureID());

			std::vector<std::string> textureOrder = { "diffuse", "specular" };
			defMat->SetTextureOrder(textureOrder);

			defMat->SetColor(Utils::Color(Utils::COLOR::MAGENTA));

			SetMaterial(DEFAULT_MISSING_MAT_NAME, defMat);
		}

	}
}
#include "MaterialManager.h"

#include "TextureImporter/TextureImporter.h"
#include "ShaderManager/ShaderManager.h"

#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	namespace Managers
	{
		using namespace FlyEngine::Materials;

		std::unordered_map<std::string, Materials::Material*> MaterialManager::materialsMap;

		void MaterialManager::InitializeManager()
		{
			CreateMaterial(DEFAULT_MAT_NAME);
			Materials::Material* defMat = GetMaterial(DEFAULT_MAT_NAME);
			defMat->AddTexture("diffuse", Importers::TextureImporter::LoadTexture("res/Textures/White.png", true));
			defMat->AddTexture("specular", Importers::TextureImporter::LoadTexture("res/Textures/White.png", true));

			std::vector<std::string> textureOrder = { "diffuse", "specular" };
			defMat->SetTextureOrder(textureOrder);
			SetMaterial(DEFAULT_MAT_NAME, defMat);
		}

		void MaterialManager::CreateMaterial(std::string materialName, std::string shaderName)
		{
			if (GetMaterial(materialName) != nullptr)
				return;
			if(shaderName != ShaderManager::DEFAULT_SHADER_NAME)
				materialsMap[materialName] = new Materials::Material(materialName, ShaderManager::GetShader(shaderName));
			else
				materialsMap[materialName] = new Materials::Material(materialName, ShaderManager::GetDefaultShader());
			std::string text = "Material Created: [" + materialName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 1, 1);
			return ;
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

			std::string text = "Edited Created: [" + matName + "]!";
			Utils::Debugger::ConsoleMessage(&text[0], 1, 0, 0, 1);
		}

		Materials::Material* MaterialManager::GetDefaultMaterial()
		{
			return GetMaterial(DEFAULT_MAT_NAME);
		}

	}
}
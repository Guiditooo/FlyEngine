#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <iostream>
#include <unordered_map>

#include "Material/Material.h"
#include "ShaderManager/ShaderManager.h"

namespace FlyEngine
{
	namespace Materials
	{
		const std::string DEFAULT_MODEL_MAT_NAME = "Default_Model_Material";
		const std::string DEFAULT_BASIC_MAT_NAME = "Default_Basic_Material";
		const std::string DEFAULT_MISSING_MAT_NAME = "Missing_Material";
	}

	namespace Managers
	{
		
		class FLY_API MaterialManager
		{
		private:
			static std::unordered_map<std::string, Materials::Material*> materialsMap;
			static void CreateBasicMaterial();
			static void CreateModelMaterial();
			static void CreateMissingMaterial();
		public:
			static void InitializeManager();
			static void CreateMaterial(std::string materialName, Shader* shader);
			static void EraseMaterial(std::string materialName);
			static Materials::Material* GetMaterial(std::string name);
			static void SetMaterial(std::string matName, Materials::Material* mat);
			static Materials::Material* GetDefaultModelMaterial();
			static Materials::Material* GetDefaultBasicMaterial();
			static Materials::Material* GetDefaultMissingMaterial();

			static bool AddTexture(std::string materialName, std::string name, int texture);
			static void SetTextureOrder(const std::string& materialName, const std::vector<std::string>& order);
		};
	}
}

#endif // !MAGERIAL_MANAGER_H

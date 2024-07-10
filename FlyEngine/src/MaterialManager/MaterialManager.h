#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include <iostream>
#include <unordered_map>

#include "Material/Material.h"

namespace FlyEngine
{
	namespace Materials
	{
		const std::string DEFAULT_MAT_NAME = "Default_Material";
	}

	namespace Managers
	{
		class FLY_API MaterialManager
		{
		private:
			static std::unordered_map<std::string, Materials::Material*> materialsMap;
		public:
			static void InitializeManager();
			static void CreateMaterial(std::string materialName, std::string shaderName = Materials::DEFAULT_MAT_NAME);
			static Materials::Material* GetMaterial(std::string name);
			static void SetMaterial(std::string matName, Materials::Material* mat);
			static Materials::Material* GetDefaultMaterial();
		};
	}
}

#endif // !MAGERIAL_MANAGER_H

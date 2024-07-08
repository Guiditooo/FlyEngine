#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Texture/Texture.h"
#include "MaterialSpecification/MaterialSpecification.h"



namespace FlyEngine
{
	class Shader;

	namespace Materials
	{
		class FLY_API Material
		{
		private:
			std::string name;
			MaterialSpecification* specs;
			std::unordered_map<std::string, Texture*> textureMap;
			std::vector<std::string> textureOrder;
			Shader* shader;
		public:
			Material(std::string name, Shader* shader);
			~Material();

			void ApplyTextures();

			void AddTexture(const std::string& name, Texture* texture);

			void SetTextureOrder(const std::vector<std::string>& order);
			void SetSpecs(MaterialSpecification* newSpecs);

			Texture* GetTexture(const std::string& name) const;
			MaterialSpecification* GetSpecs();
			std::string GetName();

			Shader* GetShader();
		};
	}
}
#endif // !MATERIAL_H
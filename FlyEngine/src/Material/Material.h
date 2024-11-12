#ifndef MATERIAL_H
#define MATERIAL_H

#include <unordered_map>
#include <vector>
#include <string>

#include "Texture/Texture.h"
#include "MaterialSpecification/MaterialSpecification.h"
#include "FlyFunctions/Color/Color.h"


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
			std::unordered_map<std::string, int> textureMap;
			//std::unordered_map<std::string, Texture*> textureMap;
			std::vector<std::string> textureOrder;
			Shader* shader;
			Utils::Color color;
		public:
			Material(std::string name, Shader* shader = nullptr);
			~Material();

			void ApplyTextures();

			bool AddTexture(const std::string& name, int textureID);
			//bool AddTexture(const std::string& name, Texture* texture);

			void SetTextureOrder(const std::vector<std::string>& order);
			void SetSpecs(MaterialSpecification* newSpecs);

			void SetColor(Utils::Color newColor);
			void SetColor(glm::vec3 newColor);
			void SetColor(glm::vec4 newColor);
			void SetColor(float r, float g, float b);
			void SetColor(float r, float g, float b, float a);

			const std::unordered_map<std::string, int>& GetTextureMap() const;

			std::vector<std::string> GetTextureOrder();
			int GetTexture(const std::string& name) const;
			MaterialSpecification* GetSpecs();
			std::string GetName();
			Utils::Color GetColor();
			glm::vec3 GetColorV3();

			Shader* GetShader();
			unsigned int GetShaderID();
		};
	}
}
#endif // !MATERIAL_H
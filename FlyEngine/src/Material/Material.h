#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "MaterialSpecification/MaterialSpecification.h"
#include "Shader/Shader.h"

namespace FlyEngine
{
	namespace Materials
	{
		class FLY_API Material
		{
		private:
			Shader* shader;
			MaterialSpecification* specs;
		public:
			Material();
			Material(const char* fragmentShaderPath, const char* vertexShaderPath);
			~Material();

			int GetShaderID();
			MaterialSpecification* GetSpecs();
			void Apply();
		};
	}
}

#endif // !MATERIAL_H
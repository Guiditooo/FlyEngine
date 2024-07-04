#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>

#include "MaterialSpecification/MaterialSpecification.h"

namespace FlyEngine
{
	namespace Materials
	{
		class FLY_API Material
		{
		private:
			MaterialSpecification* specs;
		public:
			Material();
			~Material();

			MaterialSpecification* GetSpecs();
		};
	}
}

#endif // !MATERIAL_H
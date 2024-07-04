#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Lights/Light.h"

#include <Exports/Exports.h>

namespace FlyEngine
{

	namespace Lights
	{

		class FLY_API DirectionalLight : public Light
		{
		private:
		public:
			DirectionalLight();
			DirectionalLight(glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse);
			~DirectionalLight();
		};

	}
}

#endif // !SPOT_LIGHT_H
#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

#include "Exports/Exports.h"
#include "LightType.h"

namespace FlyEngine
{

	namespace Lights
	{

		class FLY_API Light
		{
		protected:
			LightType lightType;

			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 ambient;
			glm::vec3 specular;
			glm::vec3 diffuse;

		public:
			Light(glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse, LightType type);
			~Light();

			glm::vec3 GetPosition();
			glm::vec3 GetDirection();
			glm::vec3 GetAmbient();
			glm::vec3 GetSpecular();
			glm::vec3 GetDiffuse();
			LightType GetLightType();
		};

	}
}

#endif // !LIGHT_H
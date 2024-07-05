#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Lights/Light.h"

#include <Exports/Exports.h>

namespace FlyEngine
{

	namespace Lights
	{

		class FLY_API PointLight : public Light
		{
		protected:
			float constant;
			float linear;
			float quadratic;
		public:
			PointLight();
			PointLight(float lConstant, float lLinear, float lQuadratic);
			PointLight(float lConstant, float lLinear, float lQuadratic, glm::vec3 lPosition, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse);
			~PointLight();

			float GetConstant();
			float GetLinear();
			float GetQuadratic();
		};

	}
}

#endif // !SPOT_LIGHT_H
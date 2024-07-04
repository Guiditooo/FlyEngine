#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Lights/Light.h"

#include <Exports/Exports.h>

namespace FlyEngine
{

	namespace Lights
	{

		class FLY_API SpotLight : public Light
		{
		private:
			float cutOff;
			float outerCutOff;

			float constant;
			float linear;
			float quadratic;
		public:
			SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff);
			SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff, glm::vec3 lDirection, glm::vec3 lPosition, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse);
			~SpotLight();

			float GetConstant();
			float GetLinear();
			float GetQuadratic();
			float GetCutOff();
			float GetOuterCutOff();
		};

	}
}

#endif // !SPOT_LIGHT_H
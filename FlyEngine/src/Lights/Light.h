#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>

#include <glm/glm.hpp>

#include "Exports/Exports.h"
#include "LightType.h"
#include "FlyFunctions/Color/Color.h"

namespace FlyEngine
{

	namespace Lights
	{

		class FLY_API Light
		{
		protected:
			std::string name;

			LightType lightType;

			glm::vec3 position;
			glm::vec3 direction;
			glm::vec3 ambient;
			glm::vec3 specular;
			glm::vec3 diffuse;

			FlyEngine::Utils::Color color;

			bool isActive;
		public:
			Light(glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse, LightType type);
			~Light();

			std::string GetName();
			glm::vec3 GetPosition();
			glm::vec3 GetDirection();
			glm::vec3 GetAmbient();
			glm::vec3 GetSpecular();
			glm::vec3 GetDiffuse();
			LightType GetLightType();
			FlyEngine::Utils::Color GetColor();

			void SetName(std::string newName);
			void SetPosition(glm::vec3 newPosition);
			void SetDirection(glm::vec3 newDirection);
			void SetAmbient(glm::vec3 newAmbient);
			void SetSpecular(glm::vec3 newSpecular);
			void SetDiffuse(glm::vec3 newDiffuse);
			void SetActive(bool enabled);
			void SetColor(FlyEngine::Utils::Color newColor);
			void SetColor(FlyEngine::Utils::COLOR newColor);

			bool IsActive();
		};

	}
}

#endif // !LIGHT_H
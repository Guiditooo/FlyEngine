#include "DirectionalLight.h"

FlyEngine::Lights::DirectionalLight::DirectionalLight() : Light
	(
		glm::vec3(0.0f),			 //position
		glm::vec3(0, -1, 0),		 //direction
		glm::vec3(0.05f, 0.05f, 0.05f), //ambient
		glm::vec3(0.6f, 0.6f, 0.6f), //specular
		glm::vec3(0.2f, 0.2f, 0.2f), //diffuse
		LightType::Directional		 //type
	)
{
	name = "Directional Light";
}

FlyEngine::Lights::DirectionalLight::DirectionalLight(glm::vec3 lDirection,  glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(glm::vec3(0.0f), lDirection, lAmbient, lSpecular, lDiffuse, LightType::Directional)
{
	name = "Directional Light";
}

FlyEngine::Lights::DirectionalLight::~DirectionalLight()
{
}

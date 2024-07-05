#include "PointLight.h"

FlyEngine::Lights::PointLight::PointLight() : Light
(
	glm::vec3(0.0f),				 //position
	glm::vec3(0.0f),				 //direction
	glm::vec3(0.05f, 0.05f, 0.05f),	 //ambient
	glm::vec3(0.8f, 0.8f, 0.8f),   	 //diffuse
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //specular
	LightType::Point				 //type
)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032f;

	name = "Point Light";
}

FlyEngine::Lights::PointLight::PointLight(float lConstant, float lLinear, float lQuadratic) : Light
(
	glm::vec3(0.0f),				 //position
	glm::vec3(0.0f),				 //direction
	glm::vec3(0.05f, 0.05f, 0.05f),	 //ambient
	glm::vec3(0.8f, 0.8f, 0.8f),   	 //diffuse
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //specular
	LightType::Point				 //type
)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;

	name = "Point Light";
}

FlyEngine::Lights::PointLight::PointLight(float lConstant, float lLinear, float lQuadratic, glm::vec3 lPosition, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(lPosition, glm::vec3(0.0f), lAmbient, lSpecular, lDiffuse, LightType::Point)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;

	name = "Point Light";
}

FlyEngine::Lights::PointLight::~PointLight(){}

float FlyEngine::Lights::PointLight::GetConstant()
{
	return constant;
}

float FlyEngine::Lights::PointLight::GetLinear()
{
	return linear;
}

float FlyEngine::Lights::PointLight::GetQuadratic()
{
	return quadratic;
}

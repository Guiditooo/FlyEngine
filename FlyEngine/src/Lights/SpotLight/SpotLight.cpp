#include "SpotLight.h"

FlyEngine::Lights::SpotLight::SpotLight() : Light
(
	glm::vec3(0.0f),				 //position
	glm::vec3(0.0f),				 //direction
	glm::vec3(0.0f, 0.0f, 0.0f),	 //ambient
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //diffuse
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //specular
	LightType::Spot				 //type
)
{
	constant = 1.0f;
	linear = 0.09f;
	quadratic = 0.032;
	cutOff = glm::cos(glm::radians(12.5f));
	outerCutOff = glm::cos(glm::radians(15.0f));

	name = "Spot Light";
}

FlyEngine::Lights::SpotLight::SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff) : Light
(
	glm::vec3(0.0f),				 //position
	glm::vec3(0.0f),				 //direction
	glm::vec3(0.0f, 0.0f, 0.0f),	 //ambient
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //diffuse
	glm::vec3(1.0f, 1.0f, 1.0f),   	 //specular
	LightType::Spot				 //type
)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
	cutOff = lCutOff;
	outerCutOff = lOuterCutOff;

	name = "Spot Light";
}

FlyEngine::Lights::SpotLight::SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff, glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(lPosition, lDirection, lAmbient, lSpecular, lDiffuse, LightType::Spot)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
	cutOff = lCutOff;
	outerCutOff = lOuterCutOff;

	name = "Spot Light";
}

FlyEngine::Lights::SpotLight::~SpotLight() {}

float FlyEngine::Lights::SpotLight::GetConstant()
{
	return constant;
}

float FlyEngine::Lights::SpotLight::GetLinear()
{
	return linear;
}

float FlyEngine::Lights::SpotLight::GetQuadratic()
{
	return quadratic;
}

float FlyEngine::Lights::SpotLight::GetCutOff()
{
	return cutOff;
}

float FlyEngine::Lights::SpotLight::GetOuterCutOff()
{
	return outerCutOff;
}

void FlyEngine::Lights::SpotLight::SetCutOff(float newCutOff)
{
	cutOff = newCutOff;
}

void FlyEngine::Lights::SpotLight::SetOuterCutOff(float newOuterCutOff)
{
	outerCutOff = newOuterCutOff;
}

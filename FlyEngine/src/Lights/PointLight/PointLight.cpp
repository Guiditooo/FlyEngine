#include "PointLight.h"

FlyEngine::Lights::PointLight::PointLight(float lConstant, float lLinear, float lQuadratic) : Light(glm::vec3(0.0f), glm::vec3(0.0f),glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f))
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
}

FlyEngine::Lights::PointLight::PointLight(float lConstant, float lLinear, float lQuadratic, glm::vec3 lPosition, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(lPosition, glm::vec3(0.0f), lAmbient, lSpecular, lDiffuse)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
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

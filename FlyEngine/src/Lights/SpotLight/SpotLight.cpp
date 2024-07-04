#include "SpotLight.h"

FlyEngine::Lights::SpotLight::SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff) : Light(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), LightType::Spot)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
	cutOff = lCutOff;
	outerCutOff = lOuterCutOff;
}

FlyEngine::Lights::SpotLight::SpotLight(float lConstant, float lLinear, float lQuadratic, float lCutOff, float lOuterCutOff, glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(lPosition, lDirection, lAmbient, lSpecular, lDiffuse, LightType::Spot)
{
	constant = lConstant;
	linear = lLinear;
	quadratic = lQuadratic;
	cutOff = lCutOff;
	outerCutOff = lOuterCutOff;
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

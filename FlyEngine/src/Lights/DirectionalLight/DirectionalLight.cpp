#include "DirectionalLight.h"

FlyEngine::Lights::DirectionalLight::DirectionalLight() : Light(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f)) 
{
}

FlyEngine::Lights::DirectionalLight::DirectionalLight(glm::vec3 lDirection,  glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse) : Light(glm::vec3(0.0f), lDirection, lAmbient, lSpecular, lDiffuse)
{
}

FlyEngine::Lights::DirectionalLight::~DirectionalLight()
{
}

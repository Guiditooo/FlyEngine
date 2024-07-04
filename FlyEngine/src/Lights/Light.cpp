#include "Light.h"

FlyEngine::Lights::Light::Light(glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse, LightType type)
{
    position = lPosition;
    direction = lDirection;
    ambient = lAmbient;
    specular = lSpecular;
    diffuse = lDiffuse;
    lightType = type;
}

FlyEngine::Lights::Light::~Light(){}

glm::vec3 FlyEngine::Lights::Light::GetPosition()
{
    return position;
}

glm::vec3 FlyEngine::Lights::Light::GetDirection()
{
    return direction;
}

glm::vec3 FlyEngine::Lights::Light::GetAmbient()
{
    return ambient;
}

glm::vec3 FlyEngine::Lights::Light::GetSpecular()
{
    return specular;
}

glm::vec3 FlyEngine::Lights::Light::GetDiffuse()
{
    return diffuse;
}

FlyEngine::Lights::LightType FlyEngine::Lights::Light::GetLightType()
{
    return lightType;
}


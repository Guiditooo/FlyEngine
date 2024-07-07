#include "Light.h"

FlyEngine::Lights::Light::Light(glm::vec3 lPosition, glm::vec3 lDirection, glm::vec3 lAmbient, glm::vec3 lSpecular, glm::vec3 lDiffuse, LightType type)
{
    position = lPosition;
    direction = lDirection;
    ambient = lAmbient;
    specular = lSpecular;
    diffuse = lDiffuse;
    lightType = type;

    color.SetColor(Utils::COLOR::WHITE);

    isActive = true;
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

FlyEngine::Utils::Color FlyEngine::Lights::Light::GetColor()
{
    return color;
}

void FlyEngine::Lights::Light::SetPosition(glm::vec3 newPosition)
{
    position = newPosition;
}

void FlyEngine::Lights::Light::SetDirection(glm::vec3 newDirection)
{
    direction = newDirection;
}

void FlyEngine::Lights::Light::SetAmbient(glm::vec3 newAmbient)
{
    ambient = newAmbient;
}

void FlyEngine::Lights::Light::SetSpecular(glm::vec3 newSpecular)
{
    specular = newSpecular;
}

void FlyEngine::Lights::Light::SetDiffuse(glm::vec3 newDiffuse)
{
    diffuse = newDiffuse;
}

void FlyEngine::Lights::Light::SetActive(bool enabled)
{
    isActive = enabled;
}

void FlyEngine::Lights::Light::SetColor(FlyEngine::Utils::Color newColor)
{
    color.SetColor(newColor);
}

void FlyEngine::Lights::Light::SetColor(FlyEngine::Utils::COLOR newColor)
{
    color.SetColor(newColor);
}

void FlyEngine::Lights::Light::SetName(std::string newName)
{
    name = newName;
}

bool FlyEngine::Lights::Light::IsActive()
{
    return isActive;
}

std::string FlyEngine::Lights::Light::GetName()
{
    return name;
}
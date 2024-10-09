#include "Plane.h"

FlyEngine::Plane::Plane()
{
	normal = glm::vec3(0.0f, 0.0f, 0.0f); 
	distance = 0.0f;
}

FlyEngine::Plane::Plane(glm::vec3 normal, float distance)
{
	this->normal = glm::normalize(normal);
	this->distance = distance;
}

FlyEngine::Plane::Plane(glm::vec3 normal, glm::vec3 point)
{
	this->normal = glm::normalize(normal);
	this->distance = glm::dot(normal, point);
}

FlyEngine::Plane::Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
	distance = glm::dot(normal, p1);
}

float FlyEngine::Plane::GetDistanceToPoint(glm::vec3 point)
{
	return glm::dot(normal, point) - distance;
}

bool FlyEngine::Plane::IsPointInFront(glm::vec3 point)
{
	return GetDistanceToPoint(point) > 0;
}

#include "Plane.h"

#include "glm/glm.hpp"

namespace FlyEngine
{
	int Plane::planeCount = 0;


	void Plane::AsignID()
	{
		ID = planeCount;
		planeCount++;
	}

	Plane::Plane()
	{
		normal = glm::vec3(0.0f, 0.0f, 0.0f);
		distance = 0.0f; 
		AsignID();
	}

	Plane::Plane(glm::vec3 normal, float distance)
	{
		this->normal = glm::normalize(normal);
		this->distance = distance;
		AsignID();
	}

	Plane::Plane(glm::vec3 normal, glm::vec3 point)
	{
		this->normal = glm::normalize(normal);
		this->distance = glm::dot(normal, point);
		AsignID();
	}

	Plane::Plane(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
	{
		normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));
		distance = glm::dot(normal, p1);
		AsignID();
	}

	Plane::~Plane()
	{
	}

	int Plane::GetID()
	{
		return ID;
	}

	glm::vec3 Plane::GetNormal()
	{
		return normal;
	}

	float Plane::GetDistanceToPoint(glm::vec3 point)
	{
		return glm::dot(normal, point) - distance;
	}

	bool Plane::Equals(const Plane* other)
	{
		if (other == nullptr) return false;

		const float epsilon = 1e-6f;

		bool normalEquals = glm::length(this->normal - other->normal) < epsilon;

		bool distanceEquals = std::fabs(this->distance - other->distance) < epsilon;

		return normalEquals && distanceEquals;
	}

	bool Plane::IsPointInFront(glm::vec3 point)
	{
		return GetDistanceToPoint(point) > 0;
	}
}
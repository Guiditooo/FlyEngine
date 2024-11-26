#include "TransformPosition.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FlyEngine
{
	TransformPosition::TransformPosition()
	{
		matrix = glm::mat4(1.0f);
		vector = glm::vec3(0.0f);
	}

	void TransformPosition::SetPosition(float x, float y, float z)
	{
		vector = glm::vec3(x, y, z);
		matrix = glm::translate(glm::mat4(1.0f), vector);
	}

	void TransformPosition::SetPosition(float x)
	{
		SetPosition(x, x, x);
	}

	void TransformPosition::SetPosition(glm::vec3 pos)
	{
		SetPosition(pos.x, pos.y, pos.z);
	}

	void TransformPosition::Translate(float x, float y, float z)
	{
		vector += glm::vec3(x, y, z);
		matrix = glm::translate(glm::mat4(1.0f), vector);
	}

	void TransformPosition::Translate(glm::vec3 pos)
	{
		Translate(pos.x, pos.y, pos.z);
	}

	glm::vec3 TransformPosition::GetPosition()
	{
		return vector;
	}
}
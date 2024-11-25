#include "TransformScale.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FlyEngine
{
	void TransformScale::SetScale(float x, float y, float z)
	{
		vector = glm::vec3(x, y, z);
		matrix = glm::scale(glm::mat4(1.0f), vector);
	}

	void TransformScale::SetScale(glm::vec3 scale)
	{
		SetScale(scale.x, scale.y, scale.z);
	}

	void TransformScale::SetScale(float scale)
	{
		SetScale(scale, scale, scale);
	}

	glm::vec3 TransformScale::GetScale()
	{
		return vector;
	}

	void TransformScale::Scale(float x, float y, float z)
	{
		vector *= glm::vec3(x, y, z);
		matrix = glm::scale(glm::mat4(1.0f), vector);
	}

	void TransformScale::Scale(glm::vec3 scale)
	{
		Scale(scale.x, scale.y, scale.z);
	}

	void TransformScale::Scale(float scale)
	{
		Scale(scale, scale, scale);
	}
}
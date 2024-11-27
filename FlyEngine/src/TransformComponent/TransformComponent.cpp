#include "TransformComponent.h"

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>  

namespace FlyEngine
{
	TransformComponent::TransformComponent()
	{
		position = new TransformPosition();
		rotation = new TransformRotation();
		scale = new TransformScale();
		matrix = glm::mat4(1.0f);
	}
	TransformComponent::~TransformComponent()
	{
	}
	glm::mat4 TransformComponent::GetTRS()
	{
		return matrix;
	}

	void TransformComponent::UpdateTRS()
	{
		matrix = position->matrix * rotation->matrix * scale->matrix;
	}
	
	void TransformComponent::SetFront(glm::vec3 front)
	{
		glm::vec3 newFront = glm::normalize(front);

		glm::vec3 upVector = fabs(newFront.y) > 0.999f ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::normalize(glm::cross(upVector, newFront));
		glm::vec3 up = glm::cross(newFront, right);

		matrix[0] = glm::vec4(right, 0.0f);
		matrix[1] = glm::vec4(up, 0.0f);
		matrix[2] = glm::vec4(newFront, 0.0f);

		float pitch = glm::degrees(asin(-newFront.y));
		float yaw = glm::degrees(atan2(newFront.x, newFront.z)); 

		rotation->SetRotation(glm::vec3(pitch, yaw, 0.0f));
	}

	void TransformComponent::SetUp(glm::vec3 up)
	{
		glm::vec3 newUp = glm::normalize(up);

		glm::vec3 reference = fabs(newUp.x) > 0.999f ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(1.0f, 0.0f, 0.0f);
		glm::vec3 front = glm::normalize(glm::cross(newUp, reference));
		glm::vec3 right = glm::cross(newUp, front);

		matrix[0] = glm::vec4(right, 0.0f);
		matrix[1] = glm::vec4(newUp, 0.0f);
		matrix[2] = glm::vec4(front, 0.0f);

		float pitch = glm::degrees(asin(-front.y));
		float yaw = glm::degrees(atan2(front.x, front.z));

		rotation->SetRotation(glm::vec3(pitch, yaw, 0.0f)); 
	}

	void TransformComponent::SetRight(glm::vec3 right)
	{
		glm::vec3 newRight = glm::normalize(right);

		glm::vec3 reference = fabs(newRight.y) > 0.999f ? glm::vec3(0.0f, 0.0f, 1.0f) : glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 front = glm::normalize(glm::cross(reference, newRight));
		glm::vec3 up = glm::cross(front, newRight);

		matrix[0] = glm::vec4(newRight, 0.0f);
		matrix[1] = glm::vec4(up, 0.0f);
		matrix[2] = glm::vec4(front, 0.0f);

		float pitch = glm::degrees(asin(-front.y));
		float yaw = glm::degrees(atan2(front.x, front.z));

		rotation->SetRotation(glm::vec3(pitch, yaw, 0.0f)); 
	}

	glm::vec3 TransformComponent::GetRight()
	{
		return glm::vec3(matrix[0]);
	}

	glm::vec3 TransformComponent::GetUp()
	{
		return glm::vec3(matrix[1]);
	}

	glm::vec3 TransformComponent::GetFront()
	{
		return glm::vec3(matrix[2]);
	}

	void TransformComponent::Reset()
	{
		position->SetPosition(0, 0, 0);
		rotation->SetRotation(0, 0, 0);
		scale->SetScale(1);
	}
}
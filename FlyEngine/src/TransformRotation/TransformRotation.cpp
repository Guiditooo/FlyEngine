#include "TransformRotation.h"

#include <glm/gtc/matrix_transform.hpp>

namespace FlyEngine
{

	glm::vec3 GetRight(glm::quat quaternion)
	{
		return quaternion * glm::vec3(1.0f, 0.0f, 0.0f);
	}
	glm::vec3 GetUp(glm::quat quaternion)
	{
		return quaternion * glm::vec3(0.0f, 1.0f, 0.0f);
	}
	glm::vec3 GetFront(glm::quat quaternion)
	{
		return quaternion * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	void TransformRotation::SetRotation(float x, float y, float z)
	{
		vector = glm::vec3(x, y, z);
		quaternion = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
		matrix = glm::toMat4(quaternion);
	}

	void TransformRotation::SetRotation(glm::vec3 rot)
	{
		SetRotation(rot.x, rot.y, rot.z);
	}

	void TransformRotation::SetRotation(glm::quat rot)
	{
		quaternion = rot;
		vector = glm::eulerAngles(quaternion);
		matrix = glm::toMat4(quaternion);
	}

	glm::vec3 TransformRotation::GetRotation()
	{
		return vector;
	}

	void TransformRotation::RotateAround(float x, float y, float z)
	{
		const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

		vector = glm::vec3(x, y, z);
		matrix = transformY * transformX * transformZ;
		quaternion = glm::quat_cast(matrix); 
	}

	void TransformRotation::Rotate(float x, float y, float z)
	{
		glm::quat rotX = glm::angleAxis(glm::radians(x), GetRight(quaternion));
		glm::quat rotY = glm::angleAxis(glm::radians(y), GetUp(quaternion));
		glm::quat rotZ = glm::angleAxis(glm::radians(z), GetFront(quaternion));
		glm::quat rot = rotZ * rotY * rotX;

		quaternion *= rot;

		vector = glm::eulerAngles(quaternion);
		matrix = glm::mat4_cast(quaternion);
	}

	void TransformRotation::Rotate(glm::vec3 rot)
	{
		Rotate(rot.x, rot.y, rot.z);
	}
	void TransformRotation::Rotate(glm::quat rot)
	{
		quaternion *= rot;

		vector = glm::eulerAngles(quaternion);
		matrix = glm::mat4_cast(quaternion);
	}

}

#ifndef TRANSFORM_ROTATION_H
#define TRANSFORM_ROTATION_H

#include "Exports/Exports.h"
#include "TransformElement/TransformElement.h"

namespace FlyEngine
{
	struct FLY_API TransformRotation : TransformElement
	{
	private: 
		glm::quat quaternion;

	public:
		void SetRotation(float x, float y, float z);
		void SetRotation(glm::vec3 rot);
		void SetRotation(glm::quat rot);

		glm::vec3 GetRotation();

		void RotateAround(float x, float y, float z);
		void Rotate(float x, float y, float z);
		void Rotate(glm::vec3 rot);
		void Rotate(glm::quat rot);
	};
}

#endif // !TRANSFORM_ROTATION_H
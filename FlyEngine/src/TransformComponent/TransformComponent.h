#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Exports/Exports.h"

#include "TransformPosition/TransformPosition.h"
#include "TransformRotation/TransformRotation.h"
#include "TransformScale/TransformScale.h"

namespace FlyEngine
{
	struct FLY_API TransformComponent
	{
	private:
	public:
		TransformPosition* position;
		TransformRotation* rotation;
		TransformScale* scale;
		glm::mat4 matrix;
		
		glm::mat4 GetTRS();
		void UpdateTRS();

		void SetFront(glm::vec3 front);
		void SetUp(glm::vec3 up);
		void SetRight(glm::vec3 right);

		glm::vec3 GetRight();
		glm::vec3 GetUp();
		glm::vec3 GetFront();

		void Reset();
	};

}

#endif // !TRANSFORM_COMPONENT_H
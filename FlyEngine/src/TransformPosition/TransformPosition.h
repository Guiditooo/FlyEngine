#ifndef TRANSFORM_POSITION_H
#define TRANSFORM_POSITION_H

#include "Exports/Exports.h"
#include "TransformElement/TransformElement.h"

namespace FlyEngine
{

	struct FLY_API TransformPosition : TransformElement
	{
	public:
		TransformPosition();

		void SetPosition(float x, float y, float z);
		void SetPosition(float x);
		void SetPosition(glm::vec3 pos);

		glm::vec3 GetPosition();

		void Translate(float x, float y, float z);
		void Translate(glm::vec3 pos);
	};
}

#endif // !TRANSFORM_POSITION_H
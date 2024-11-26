#ifndef TRANSFORM_SCALE_H
#define TRANSFORM_SCALE_H

#include "Exports/Exports.h"
#include "TransformElement/TransformElement.h"

namespace FlyEngine
{

	struct FLY_API TransformScale : TransformElement
	{
	public:
		TransformScale();

		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);

		glm::vec3 GetScale();

		void Scale(float x, float y, float z);
		void Scale(glm::vec3 scale);
		void Scale(float scale);
	};
}

#endif // !TRANSFORM_SCALE_H
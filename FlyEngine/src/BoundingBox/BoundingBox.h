#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <glm/vec3.hpp>

namespace FlyEngine
{
	namespace Utils
	{
		struct BoundingBox
		{
			glm::vec3 min;
			glm::vec3 max;
		};
	}
}
#endif // !BOUNDING_BOX_H

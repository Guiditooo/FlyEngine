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

			BoundingBox()
			{
				min = glm::vec3();
				max = glm::vec3();
			}

			BoundingBox(glm::vec3 m, glm::vec3 M)
			{
				min = m;
				max = M;
			}

			static BoundingBox Merge(BoundingBox one, BoundingBox two)
			{
				BoundingBox a;
				a.min = glm::min(one.min, two.min);
				a.max = glm::max(one.max, two.max);
				return a;
			}

			bool IsValid()
			{
				return min.x <= max.x && min.y <= max.y && min.z <= max.z;
			}

			static BoundingBox TransformBoundingBox(Utils::BoundingBox& bbox, glm::mat4& modelMatrix)
			{
				glm::vec3 corners[8] = 
				{
					bbox.min,
					glm::vec3(bbox.max.x, bbox.min.y, bbox.min.z),
					glm::vec3(bbox.min.x, bbox.max.y, bbox.min.z),
					glm::vec3(bbox.min.x, bbox.min.y, bbox.max.z),
					glm::vec3(bbox.max.x, bbox.max.y, bbox.min.z),
					glm::vec3(bbox.max.x, bbox.min.y, bbox.max.z),
					glm::vec3(bbox.min.x, bbox.max.y, bbox.max.z),
					bbox.max
				};

				BoundingBox transformedBBox;

				for (const glm::vec3& corner : corners)
				{
					glm::vec3 transformedCorner = glm::vec3(modelMatrix * glm::vec4(corner, 1.0f));
					BoundingBox aux = BoundingBox(transformedCorner, transformedCorner);
					transformedBBox = Merge(aux, transformedBBox);
				}

				return transformedBBox;
			}

		};
	}
}
#endif // !BOUNDING_BOX_H

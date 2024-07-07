#ifndef VERTEX_H
#define VERTEX_H

#include "glm/glm.hpp"
#include "Exports/Exports.h"

namespace FlyEngine
{
	namespace Entities
	{
		#define MAX_BONE_INFLUENCE 4
		struct FLY_API Vertex
		{
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
			glm::vec3 Tangent;
			glm::vec3 Bitangent;
			int m_BoneIDs[MAX_BONE_INFLUENCE];
			float m_Weights[MAX_BONE_INFLUENCE];
		};
	}
}
#endif // !VERTEX_H

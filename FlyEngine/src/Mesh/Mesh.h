#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <string>

#include "Exports/Exports.h"

namespace FlyEngine
{

	class Shader;

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

		struct FLY_API Texture
		{
			unsigned int id;
			std::string type;
			std::string path;
		};

		class FLY_API Mesh
		{
		public:
			std::vector<Entities::Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Entities::Texture> textures;
			unsigned int VAO;

			Mesh(std::vector<Entities::Vertex> vertices, std::vector<unsigned int> indices, std::vector<Entities::Texture> textures);
			void Draw(unsigned int shaderID);
		private:
			unsigned int VBO, EBO;

			void SetupMesh();
		};

	}

}
#endif
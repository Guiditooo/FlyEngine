#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <string>

#include "Exports/Exports.h"
#include "Vertex/Vertex.h"

namespace FlyEngine
{

	class Shader;

	namespace Entities
	{

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
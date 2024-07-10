#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <string>

#include "Exports/Exports.h"
#include "Entity/Entity.h"
#include "Vertex/Vertex.h"
#include "Buffers/Buffers.h"

namespace FlyEngine
{

	class Shader;

	namespace Materials
	{
		class Material;
	}
	
	namespace Entities
	{

		class FLY_API Mesh : public Entity
		{
		private:
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			void SetupMesh();
		public:

			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Materials::Material* material);

			//Utils::Buffers GetBuffers();
			std::vector<Vertex> GetVertices();
			std::vector<unsigned int> GetIndexes();
			//Materials::Material* GetMaterial();

			//unsigned int GetShaderID();

			// Heredado vía Entity
			void Draw() override;
		};

	}

}
#endif
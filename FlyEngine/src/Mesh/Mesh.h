#ifndef MESH_H
#define MESH_H

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <string>

#include "Exports/Exports.h"
#include "Vertex/Vertex.h"
#include "Buffers/Buffers.h"

namespace FlyEngine
{
	namespace Entities
	{

		class FLY_API Mesh
		{
		private:
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;

			Utils::Buffers* buffers;

			void SetupMesh();
		public:

			Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string meshName = "Mesh");

			std::vector<Vertex> GetVertices();
			std::vector<unsigned int> GetIndexes();

		};
	}
}
#endif
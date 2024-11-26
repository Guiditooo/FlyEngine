#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <string>

#include "Exports/Exports.h"
#include "Vertex/Vertex.h"
#include "Buffers/Buffers.h"

namespace FlyEngine
{

	class FLY_API Mesh
	{
	private:
		std::vector<Entities::Vertex> vertices;
		std::vector<unsigned int> indices;

		Utils::Buffers* buffers;

		std::string name;

		void SetupMesh();
	public:

		Mesh(std::vector<Entities::Vertex> vertices, std::vector<unsigned int> indices, std::string meshName = "Mesh");

		void SetName(std::string meshName);

		Utils::Buffers* GetBuffers();
		std::vector<Entities::Vertex> GetVertices();
		std::vector<unsigned int> GetIndexes();

	};

}
#endif
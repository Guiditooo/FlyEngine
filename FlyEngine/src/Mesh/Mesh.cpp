#include "Mesh.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "Shader/Shader.h"
#include "Material/Material.h"

using namespace FlyEngine::Entities;

namespace FlyEngine
{

        Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string meshName)
		{
            this->vertices = vertices;
            this->indices = indices;

            buffers = new Utils::Buffers();

            name = meshName;

            SetupMesh();
		}

        void Mesh::SetName(std::string meshName)
        {
            name = meshName;
        }

        Utils::Buffers* Mesh::GetBuffers()
        {
            return buffers;
        }

        std::vector<Vertex> Mesh::GetVertices()
        {
            return vertices;
        }

        std::vector<unsigned int> Mesh::GetIndexes()
        {
            return indices;
        }

		void Mesh::SetupMesh()
		{
            glGenVertexArrays(1, &buffers->VAO);
            glGenBuffers(1, &buffers->VBO);
            glGenBuffers(1, &buffers->EBO);

            glBindVertexArray(buffers->VAO);
            glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

            glEnableVertexAttribArray(5);
            glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
            glBindVertexArray(0);
		}
	
}
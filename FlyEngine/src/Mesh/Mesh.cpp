#include "Mesh.h"

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "Shader/Shader.h"
#include "Material/Material.h"

namespace FlyEngine
{
	namespace Entities
	{
        Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Materials::Material* material) : Entity("Mesh")
		{
            this->vertices = vertices;
            this->indices = indices;
            this->material = material;

            // now that we have all the required data, set the vertex buffers and its attribute pointers.
            SetupMesh();
		}
        std::vector<Vertex> Mesh::GetVertices()
        {
            return vertices;
        }
        std::vector<unsigned int> Mesh::GetIndexes()
        {
            return indices;
        }
        void Mesh::Draw()
        {
        }
		void Mesh::SetupMesh()
		{
            // create buffers/arrays
            glGenVertexArrays(1, &buffers->VAO);
            glGenBuffers(1, &buffers->VBO);
            glGenBuffers(1, &buffers->EBO);

            glBindVertexArray(buffers->VAO);
            // load data into vertex buffers
            glBindBuffer(GL_ARRAY_BUFFER, buffers->VBO);
            // A great thing about structs is that their memory layout is sequential for all its items.
            // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
            // again translates to 3/2 floats which translates to a byte array.
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers->EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

            // set the vertex attribute pointers
            // vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
            // vertex normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
            // vertex texture coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
            // vertex tangent
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
            // vertex bitangent
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
            // ids
            glEnableVertexAttribArray(5);
            glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

            // weights
            glEnableVertexAttribArray(6);
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
            glBindVertexArray(0);
		}
	}
}
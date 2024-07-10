#include "Model.h"

#include <iostream>
#include <algorithm>
#include <string>

#include "ModelImporter/ModelImporter.h"
#include "Mesh/Mesh.h"

namespace FlyEngine
{
    namespace Entities
    {
        
        Model::Model(std::string modelName, bool gamma) : Entity3D(modelName)
        {
            gammaCorrection = gamma;
            useBaseMaterial = false;
        }

        void Model::Draw(unsigned int shaderID)
        {
        }

        void Model::Draw()
        {
            //Deprecated
            /*
            material->Apply();
            Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
            Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
            Renderer::DrawRequest(VAO, indexCount);
            */
        }

        void Model::UpdateMeshesTransform()
        {
            for (Mesh* mesh : meshes) 
            {
                mesh->SetPosition(positionVector);
                mesh->SetRotation(rotationVector);
                mesh->SetScale(scaleVector);
            }
        }

        void Model::SetDirectory(std::string directory)
        {
            this->directory = directory;
        }

        void Model::AddMesh(Mesh* mesh)
        {
            mesh->SetPosition(positionVector);
            mesh->SetRotation(rotationVector);
            mesh->SetScale(scaleVector);
            mesh->SetColor(color);
            std::string meshName = "Mesh";
            meshName += std::to_string(meshes.size());
            mesh->SetName(meshName);
            meshes.push_back(mesh);
        }

        glm::vec3 Model::GetDimesions()
        {
            glm::vec3 min(std::numeric_limits<float>::max());
            glm::vec3 max(std::numeric_limits<float>::lowest());

            for (Mesh* mesh : meshes) 
            {
                for (const auto& vertex : mesh->GetVertices()) 
                {
                    min.x = std::min(min.x, vertex.Position.x);
                    min.y = std::min(min.y, vertex.Position.y);
                    min.z = std::min(min.z, vertex.Position.z);

                    max.x = std::max(max.x, vertex.Position.x);
                    max.y = std::max(max.y, vertex.Position.y);
                    max.z = std::max(max.z, vertex.Position.z);
                }
            }

            return max - min;
        }
        std::vector<Mesh*> Model::GetMeshes()
        {
            return meshes;
        }
        std::string Model::GetDirectory()
        {
            return directory;
        }
        void Model::SetPosition(float x, float y, float z)
        {
            Entity::SetPosition(x, y, z);
            UpdateMeshesTransform();
        }
        void Model::SetPosition(float x)
        {
            Entity::SetPosition(x);
            UpdateMeshesTransform();
        }
        void Model::SetPosition(glm::vec3 pos)
        {
            Entity::SetPosition(pos);
            UpdateMeshesTransform();
        }
        void Model::SetRotation(float x, float y, float z)
        {
            Entity::SetRotation(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::SetRotation(glm::vec3 rot)
        {
            Entity::SetRotation(rot);
            UpdateMeshesTransform();
        }
        void Model::SetRotation(glm::quat rot)
        {
            Entity::SetRotation(rot);
            UpdateMeshesTransform();
        }
        void Model::SetScale(float x, float y, float z)
        {
            Entity::SetScale(x, y, z);
            UpdateMeshesTransform();
        }
        void Model::SetScale(glm::vec3 scale)
        {
            Entity::SetScale(scale);
            UpdateMeshesTransform();
        }
        void Model::SetScale(float scale)
        {
            Entity::SetScale(scale);
            UpdateMeshesTransform();
        }
        void Model::Translate(float x, float y, float z)
        {
            Entity::Translate(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Translate(glm::vec3 pos)
        {
            Entity::Translate(pos);
            UpdateMeshesTransform();
        }
        void Model::Rotate(float x, float y, float z)
        {
            Entity::Rotate(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Rotate(glm::vec3 rot)
        {
            Entity::Rotate(rot);
            UpdateMeshesTransform();
        }
        void Model::Scale(float x, float y, float z)
        {
            Entity::Scale(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Scale(glm::vec3 scale)
        {
            Entity::Scale(scale);
            UpdateMeshesTransform();
        }
        void Model::Scale(float scale)
        {
            Entity::Scale(scale);
            UpdateMeshesTransform();
        }
        void Model::SetColor(Utils::Color newColor)
        {
            Entity::SetColor(newColor);
            for (Mesh* mesh : meshes)
            {
                mesh->SetColor(color);
            }
        }
        void Model::SetColor(glm::vec3 newColor)
        {
            Entity::SetColor(newColor);
            for (Mesh* mesh : meshes)
            {
                mesh->SetColor(color);
            }
        }
        void Model::SetColor(float r, float g, float b)
        {
            Entity::SetColor(r,g,b);
            for (Mesh* mesh : meshes)
            {
                mesh->SetColor(color);
            }
        }
        void Model::SetColor(Utils::COLOR newColor)
        {
            Entity::SetColor(newColor);
            for (Mesh* mesh : meshes)
            {
                mesh->SetColor(color);
            }
        }
        void Model::UseBaseMaterial(bool useBaseMat)
        {
            useBaseMaterial = useBaseMat;
        }
        bool Model::ShouldUseBaseMaterial()
        {
            return useBaseMaterial;
        }
    }
}
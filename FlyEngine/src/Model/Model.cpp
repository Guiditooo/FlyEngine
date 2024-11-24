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

        void Model::UpdateMeshesTransform()
        {
            for (Mesh* mesh : meshes) 
            {
                mesh->SetPosition(transform->GetPosition()); //Darle cosas de mundo
                mesh->SetRotation(transform->GetRotation());
                mesh->SetScale(transform->GetScale());
            }
        }

        void Model::SetDirectory(std::string directory)
        {
            this->directory = directory;
        }

        void Model::AddMesh(Mesh* mesh)
        {
            mesh->SetPosition(transform->GetPosition());
            mesh->SetRotation(transform->GetRotation());
            mesh->SetScale(transform->GetScale());
            //mesh->SetColor(color);
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
            transform->Translate(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Translate(glm::vec3 pos)
        {
            transform->Translate(pos);
            UpdateMeshesTransform();
        }
        void Model::Rotate(float x, float y, float z)
        {
            transform->Rotate(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Rotate(glm::vec3 rot)
        {
            transform->Rotate(rot);
            UpdateMeshesTransform();
        }
        void Model::Scale(float x, float y, float z)
        {
            transform->Scale(x,y,z);
            UpdateMeshesTransform();
        }
        void Model::Scale(glm::vec3 scale)
        {
            transform->Scale(scale);
            UpdateMeshesTransform();
        }
        void Model::Scale(float scale)
        {
            transform->Scale(scale);
            UpdateMeshesTransform();
        }
        /*void Model::SetColor(Utils::Color newColor)
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
        }*/
        void Model::UseBaseMaterial(bool useBaseMat)
        {
            useBaseMaterial = useBaseMat;
        }
        bool Model::ShouldUseBaseMaterial()
        {
            return useBaseMaterial;
        }
        std::vector<Mesh*> Model::GetSubMeshes()
        {
            return meshes;
        }
    }
}
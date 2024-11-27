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

        void Model::SetDirectory(std::string directory)
        {
            this->directory = directory;
        }

        void Model::AddMesh(Mesh* mesh)
        {
            //mesh->SetColor(color);
            std::string meshName = "Mesh";
            meshName += std::to_string(meshes.size());
            mesh->SetName(meshName);
            meshes.push_back(mesh);
        }

        Model* Model::GetRoot()
        {
            return dynamic_cast<Model*>(transform->GetRoot()->GetEntity());
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
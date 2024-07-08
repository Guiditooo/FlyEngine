#include "Model.h"

#include <iostream>

#include "ModelImporter/ModelImporter.h"

namespace FlyEngine
{

    FlyEngine::Entities::Model::Model(bool gamma) : Entity3D("Model")
    {
        gammaCorrection = gamma;
    }

    void Entities::Model::Draw(unsigned int shaderID)
    {
        for (int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shaderID);
    }

    void Entities::Model::Draw()
    {
        //Deprecated
        /*
        material->Apply();
        Renderer::SetMatrixUniform(material->GetShaderID(), "modelMatrix", model);
        Renderer::SetVec3Uniform(material->GetShaderID(), "colorMultiplier", color.GetColorV3());
        Renderer::DrawRequest(VAO, indexCount);
        */
    }
    glm::vec3 Entities::Model::GetDimesions()
    {
        glm::vec3 min(std::numeric_limits<float>::max());
        glm::vec3 max(std::numeric_limits<float>::lowest());

        for (const auto& mesh : meshes) {
            for (const auto& vertex : mesh.vertices) {
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
}
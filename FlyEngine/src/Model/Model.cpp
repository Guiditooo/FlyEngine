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
}
#ifndef MODEL_H
#define MODEL_H

#include <assimp/scene.h>

#include "Entity3D/Entity3D.h"

#include "Shader/Shader.h"
#include "Mesh/Mesh.h"

namespace FlyEngine
{

    namespace Entities
    {
        class FLY_API Model : public Entity3D
        {
        public:
            std::vector<Entities::Texture> textures_loaded;
            std::vector<Mesh> meshes;
            std::string directory;
            bool gammaCorrection;

            Model(bool gamma = false);

            void Draw(unsigned int shaderID, glm::vec3 objColor = glm::vec3(1.0f));
            void Draw() override;
        private:
        };
    }
}

#endif // !MODEL_H
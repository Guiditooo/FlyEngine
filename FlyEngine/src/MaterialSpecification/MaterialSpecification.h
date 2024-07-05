#ifndef MATERIAL_SPEC_H
#define MATERIAL_SPEC_H

#include <Exports/Exports.h>
#include <glm/glm.hpp>

#include "Material/MaterialList.h"

namespace FlyEngine
{
    namespace Materials
    {
        class FLY_API MaterialSpecification
        {
        private:
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            float shininess;
        public:
            MaterialSpecification(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float shin);
            MaterialSpecification();
            ~MaterialSpecification();
            void SetSpecs(MaterialList material);

            glm::vec3 GetAmbient();
            glm::vec3 GetDiffuse();
            glm::vec3 GetSpecular();
            float GetShininess();
        }; 
    }
}

#endif // !MATERIAL_SPEC_H

#ifndef SCENE_H
#define SCENE_H

#include <functional>
#include <memory>
#include <vector>

#include "glm/mat4x4.hpp"

namespace FlyEngine
{
    namespace Entities
    {
        class Entity;
    }

    class Scene
    {
    public:
        Scene(Entities::Entity* entity);
        void Traverse(std::function<void(Entities::Entity*)> action, Entities::Entity* node = nullptr);

    private:
        Entities::Entity* root; // Entidad que representa este nodo
    };
}
#endif //SCENE_NODE_H
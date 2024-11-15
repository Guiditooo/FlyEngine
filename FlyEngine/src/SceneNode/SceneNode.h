#ifndef SCENE_NODE_H
#define SCENE_NODE_H

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

    class SceneNode
    {
    public:
        SceneNode(Entities::Entity* entity);

        // Getters y setters para el nodo padre
        SceneNode* GetParent() const;
        void SetParent(SceneNode* parent);

        // Métodos para gestionar hijos
        void AddChild(std::unique_ptr<SceneNode> child);
        void RemoveChild(SceneNode* child);
        const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;

        // Métodos de transformación
        void SetLocalTransform(const glm::mat4& transform);
        glm::mat4 GetLocalTransform() const;
        glm::mat4 GetGlobalTransform() const;

        // Acceso a la entidad asociada
        Entities::Entity* GetEntity() const;

        void Traverse(const std::function<void(SceneNode*, const glm::mat4&)>& func, const glm::mat4& accumulatedTransform);

    private:
        SceneNode* parent; // Puntero al nodo padre
        std::vector<std::unique_ptr<SceneNode>> children; // Nodos hijos

        Entities::Entity* entity; // Entidad que representa este nodo
        glm::mat4 localTransform; // Transformación local del nodo
    };
}
#endif //SCENE_NODE_H
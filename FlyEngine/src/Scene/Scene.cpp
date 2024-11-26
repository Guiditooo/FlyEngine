#include "Scene.h"

#include "Entity/Entity.h"

namespace FlyEngine
{
	Scene::Scene(Entities::Entity* entity) : root(entity) {}

	void Scene::Traverse(std::function<void(Entities::Entity*)> action, Entities::Entity* node)
	{
		if (node == nullptr) 
			node = root;

		action(node);
		for (Entities::Entity* child : node->GetChildren())
		{
			Traverse(action, child);
		}
	}
}
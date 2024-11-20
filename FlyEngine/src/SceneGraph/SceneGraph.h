#ifndef SCENE_GRAPH_H
#define SCENE_GRAPH_H

#include <memory>
#include <functional>

#include "SceneNode/SceneNode.h"

namespace FlyEngine
{

	class Scene
	{
	private:
		Entities::Entity* root;
	
	public:
		void AddRootNode(std::unique_ptr<SceneNode> node);

		void RemoveNode(SceneNode* node);

		const std::vector<std::unique_ptr<SceneNode>>& GetNodes() const;

		void TraverseGraph(const std::function<void(SceneNode*, const glm::mat4&)>& func);

	};
}

#endif //SCENE_GRAPH_H
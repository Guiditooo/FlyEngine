#include "SceneGraph.h"

namespace FlyEngine
{
	/*
	void SceneGraph::AddRootNode(std::unique_ptr<SceneNode> rootNode)
	{
		nodes.push_back(std::move(rootNode));
	}
	void SceneGraph::RemoveNode(SceneNode* node)
	{
		auto it = std::remove_if(nodes.begin(), nodes.end(),
			[&](const std::unique_ptr<SceneNode>& rootNode) { 
				return rootNode.get() == node;
			});
		nodes.erase(it, nodes.end());
	}
	const std::vector<std::unique_ptr<SceneNode>>& SceneGraph::GetNodes() const
	{
		return nodes;
	}
	void SceneGraph::TraverseGraph(const std::function<void(SceneNode*, const glm::mat4&)>& func)
	{
		for (auto& rootNode : nodes) {
			rootNode->Traverse(func, glm::mat4(1.0f));  // Inicia con la matriz identidad
		}
	}*/
}
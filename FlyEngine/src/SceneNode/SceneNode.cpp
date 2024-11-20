#include "SceneNode.h"

namespace FlyEngine
{
	/*
	SceneNode::SceneNode(Entities::Entity* entity) : parent(nullptr), entity(entity), localTransform(glm::mat4(1.0f)) {}

	void SceneNode::SetParent(SceneNode* parent)
	{
		this->parent = parent;
	}
	SceneNode* SceneNode::GetParent() const
	{
		return parent;
	}
	void SceneNode::AddChild(std::unique_ptr<SceneNode> child)
	{
		child->SetParent(this);
		children.push_back(std::move(child));
	}
	void SceneNode::RemoveChild(SceneNode* child)
	{
		auto it = std::remove_if(
			children.begin(), 
			children.end(),
			[&](const std::unique_ptr<SceneNode>& c) 
			{ 
				return c.get() == child; 
			}
		);
		children.erase(it, children.end());
	}
	void SceneNode::SetLocalTransform(const glm::mat4& transform)
	{
		localTransform = transform;
	}
	glm::mat4 SceneNode::GetLocalTransform() const
	{
		return localTransform;
	}
	glm::mat4 SceneNode::GetGlobalTransform() const
	{
		if (parent) 
		{
			return parent->GetGlobalTransform() * localTransform;
		}
		return localTransform;
	}
	Entities::Entity* SceneNode::GetEntity() const
	{
		return entity;
	}
	void SceneNode::Traverse(const std::function<void(SceneNode*, const glm::mat4&)>& func, const glm::mat4& accumulatedTransform)
	{
		glm::mat4 globalTransform = accumulatedTransform * localTransform;
		func(this, globalTransform);
		for (auto& child : children) 
		{
			child->Traverse(func, globalTransform);
		}
	}
	*/
}
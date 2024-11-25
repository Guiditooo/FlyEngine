#include "Transform.h"

#include <glm/gtx/euler_angles.hpp>

#include "Entity/Entity.h"

const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
const float pi = 3.14159265359f;

namespace FlyEngine
{
	void Transform::UpdateMatrices()
	{
		UpdateLocalMatrix();
		UpdateWorldMatrix();
	}

	void Transform::FreeLocalMatrix()
	{
		localTransform->matrix = worldTransform->matrix;
	}

	Transform::Transform(Entities::Entity* entity)
	{
		this->entity = entity;
		
		localTransform->Reset();
		worldTransform->Reset();

		parent = nullptr;
		children = std::vector<Transform*>();
	}

	Transform::~Transform()
	{
	}

	void Transform::SetWorldPosition(float x, float y, float z)
	{
		glm::vec3 worldPos = glm::vec3(x, y, z);

		if (parent)
		{
			glm::mat4 parentWorldMatrixInverse = glm::inverse(parent->worldTransform->matrix);
			glm::vec4 localPos = parentWorldMatrixInverse * glm::vec4(worldPos, 1.0f);

			localTransform->position->SetPosition(glm::vec3(localPos));
		}
		else
		{
			localTransform->position->SetPosition(worldPos);
		}

		UpdateMatrices();
	}

	void Transform::SetLocalPosition(float x, float y, float z)
	{
		localTransform->position->SetPosition(x, y, z);
		UpdateMatrices();
	}

	void Transform::SetWorldRotation(float x, float y, float z)
	{
		glm::quat worldQuat = glm::quat(glm::radians(glm::vec3(x, y, z)));

		if (parent)
		{
			glm::quat parentWorldQuat = glm::quat_cast(parent->worldTransform->matrix);
			glm::quat localQuat = glm::inverse(parentWorldQuat) * worldQuat;
			localTransform->rotation->SetRotation(localQuat);
		}
		else
		{
			localTransform->rotation->SetRotation(worldQuat);
		}

		UpdateMatrices();
	}

	void Transform::SetLocalRotation(float x, float y, float z)
	{
		localTransform->rotation->SetRotation(x,y,z);
		UpdateMatrices();
	}

	void Transform::SetWorldScale(float x, float y, float z)
	{
		glm::vec3 worldScale = glm::vec3 (x, y, z);

		if (parent)
		{
			glm::vec3 parentScale = parent->worldTransform->scale->GetScale();
			glm::vec3 localScale = worldScale / parentScale;
			localTransform->scale->SetScale(localScale);
		}
		else
		{
			localTransform->scale->SetScale(worldScale);
		}

		UpdateMatrices();
	}

	void Transform::SetLocalScale(float x, float y, float z)
	{
		localTransform->scale->SetScale(x, y, z);
		UpdateMatrices();
	}

	void Transform::WorldTranslate(float x, float y, float z)
	{
		glm::vec3 worldTranslation(x, y, z);

		if (parent)
		{
			glm::mat4 parentWorldMatrixInverse = glm::inverse(parent->worldTransform->matrix);
			glm::vec4 localTranslation = parentWorldMatrixInverse * glm::vec4(worldTranslation, 0.0f);
			localTransform->position->Translate(glm::vec3(localTranslation));
		}
		else
		{
			localTransform->position->Translate(worldTranslation);
		}

		UpdateMatrices();
	}

	void Transform::LocalTranslate(float x, float y, float z)
	{
		localTransform->position->Translate(x, y, z);
		UpdateMatrices();
	}

	void Transform::WorldRotate(float x, float y, float z)
	{
		glm::quat worldQuat = glm::quat(glm::radians(glm::vec3(x, y, z)));

		if (parent)
		{
			glm::quat parentWorldQuat = glm::quat_cast(parent->worldTransform->matrix);
			glm::quat localQuat = glm::inverse(parentWorldQuat) * worldQuat;
			localTransform->rotation->Rotate(localQuat);
		}
		else
		{
			localTransform->rotation->Rotate(worldQuat);
		}

		UpdateMatrices();
	}

	void Transform::LocalRotate(float x, float y, float z)
	{
		localTransform->rotation->Rotate(x, y, z);
		UpdateMatrices();
	}

	void Transform::WorldScale(float x, float y, float z)
	{
		glm::vec3 worldScaling(x, y, z);

		if (parent)
		{
			glm::vec3 parentScale = parent->worldTransform->scale->GetScale();
			glm::vec3 localScaling = worldScaling / parentScale;
			localTransform->scale->Scale(localScaling);
		}
		else
		{
			localTransform->scale->Scale(worldScaling);
		}

		UpdateMatrices();
	}

	void Transform::LocalScale(float x, float y, float z)
	{
		localTransform->scale->Scale(x, y, z);
		UpdateMatrices();
	}

	glm::vec3 Transform::GetWorldPosition()
	{
		return worldTransform->position->GetPosition();
	}

	glm::vec3 Transform::GetLocalPosition()
	{
		return localTransform->position->GetPosition();
	}

	glm::vec3 Transform::GetWorldRotation()
	{
		return worldTransform->rotation->GetRotation();
	}

	glm::vec3 Transform::GetLocalRotation()
	{
		return localTransform->rotation->GetRotation();
	}

	glm::vec3 Transform::GetWorldScale()
	{
		return worldTransform->scale->GetScale();
	}

	glm::vec3 Transform::GetLocalScale()
	{
		return localTransform->scale->GetScale();
	}


	void Transform::UpdateLocalMatrix()
	{
		localTransform->UpdateTRS();
	}

	void Transform::UpdateWorldMatrix()
	{
		if (parent)
		{
			worldTransform->matrix = parent->worldTransform->matrix * localTransform->matrix;
		}
		else
		{
			worldTransform->matrix = localTransform->matrix;
		}

		for (auto child : children)
		{
			child->UpdateWorldMatrix();
		}
	}

	Transform* Transform::GetParent()
	{
		return parent;
	}

	std::vector<Transform*> Transform::GetChildren()
	{
		return children;
	}

	void Transform::AddChild(Transform* newChild)
	{
		children.push_back(newChild);
		if (newChild->GetParent() != this)
		{
			newChild->SetParent(this);
			newChild->UpdateWorldMatrix();
		}
	}

	void Transform::SetParent(Transform* newParent)
	{
		RemoveParent();

		parent = newParent;

		if (parent)
			parent->AddChild(this);
	}

	void Transform::RemoveChild(Transform* child)
	{
		auto it = std::find(children.begin(), children.end(), child);
		if (it != children.end())
		{
			children.erase(it);
			child->RemoveParent();
			child->FreeLocalMatrix();
		}
	}

	void Transform::RemoveParent()
	{
		if (parent)
			parent->RemoveChild(this);
		FreeLocalMatrix();
	}

	void Transform::SetEntity(Entities::Entity* entity)
	{
		this->entity = entity;
	}

	Entities::Entity* Transform::GetEntity()
	{
		return entity;
	}


}
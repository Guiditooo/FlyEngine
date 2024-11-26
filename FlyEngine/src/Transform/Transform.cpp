#include "Transform.h"

#include <glm/gtx/euler_angles.hpp>

#include "Entity/Entity.h"

const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
const float pi = 3.14159265359f;

glm::vec3 Mat4ToEuler(const glm::mat4& rotationMatrix);

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
		
		localTransform = new TransformComponent();
		worldTransform = new TransformComponent();

		localTransform->Reset();
		worldTransform->Reset();

		parent = nullptr;
		children = std::vector<Transform*>();
	}

	Transform::~Transform()
	{
		if (parent)
			RemoveParent();

		if (localTransform != nullptr)
			delete localTransform;
		localTransform = nullptr;

		if (worldTransform != nullptr)
			delete worldTransform;
		worldTransform = nullptr;
	}

	void Transform::SetWorldPosition(float x, float y, float z)
	{
		glm::vec3 worldPos = glm::vec3(x, y, z);
		worldTransform->position->SetPosition(x, y, z);

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
		SetWorldRotation(worldQuat);
	}

	void Transform::SetWorldRotation(glm::quat rot)
	{
		worldTransform->rotation->SetRotation(rot);

		if (parent)
		{
			glm::quat parentWorldQuat = glm::quat_cast(parent->worldTransform->matrix);
			glm::quat localQuat = glm::inverse(parentWorldQuat) * rot;
			localTransform->rotation->SetRotation(localQuat);
		}
		else
		{
			localTransform->rotation->SetRotation(rot);
		}

		UpdateMatrices();
	}

	void Transform::SetLocalRotation(float x, float y, float z)
	{
		localTransform->rotation->SetRotation(x,y,z);
		UpdateMatrices();
	}

	void Transform::SetLocalRotation(glm::quat rot)
	{
		localTransform->rotation->SetRotation(rot);
		UpdateMatrices();
	}

	void Transform::SetWorldScale(float x, float y, float z)
	{
		glm::vec3 worldScale = glm::vec3 (x, y, z);
		worldTransform->scale->SetScale(x, y, z);

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
		worldTransform->position->Translate(x, y, z);

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
		worldTransform->rotation->Rotate(x, y, z);

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

	void Transform::WorldRotateAround(float x, float y, float z)
	{
		glm::vec3 currentLocalRotation = worldTransform->rotation->GetRotation();

		glm::mat4 globalRotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		globalRotationMatrix = glm::rotate(globalRotationMatrix, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		globalRotationMatrix = glm::rotate(globalRotationMatrix, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));

		worldTransform->rotation->SetRotation(globalRotationMatrix);

		if (parent)
		{
			
			glm::mat4 parentWorldMatrixInverse = glm::inverse(parent->GetWorldTRS());
			glm::mat4 localRotationMatrix = parentWorldMatrixInverse * globalRotationMatrix * parent->GetWorldTRS();
			glm::vec3 newLocalRotation = Mat4ToEuler(localRotationMatrix) + currentLocalRotation;
			localTransform->rotation->SetRotation(newLocalRotation);

		}

		glm::vec3 newLocalRotation = Mat4ToEuler(globalRotationMatrix) + localTransform->rotation->GetRotation();
		localTransform->rotation->SetRotation(newLocalRotation);
		UpdateMatrices();
	}

	void Transform::LocalRotateAround(float x, float y, float z)
	{
		localTransform->rotation->RotateAround(x, y, z);
		UpdateMatrices();
	}

	void Transform::WorldScale(float x, float y, float z)
	{
		glm::vec3 worldScaling(x, y, z);
		worldTransform->scale->Scale(x, y, z);

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

	void Transform::SetFront(glm::vec3 front)
	{
		localTransform->SetFront(front);
	}

	void Transform::SetUp(glm::vec3 up)
	{
		localTransform->SetUp(up);
	}

	void Transform::SetRight(glm::vec3 right)
	{
		localTransform->SetRight(right);
	}

	glm::vec3 Transform::GetFront()
	{
		return localTransform->GetFront();
	}

	glm::vec3 Transform::GetUp()
	{
		return localTransform->GetUp();
	}

	glm::vec3 Transform::GetRight()
	{
		return localTransform->GetRight();
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

	glm::mat4 Transform::GetLocalTRS()
	{
		return localTransform->GetTRS();
	}

	glm::mat4 Transform::GetWorldTRS()
	{
		return worldTransform->GetTRS();
	}

	Transform* Transform::GetParent()
	{
		return parent;
	}

	std::vector<Transform*> Transform::GetChildren()
	{
		return children;
	}

	std::vector<Transform*> Transform::GetChildrenWithName(std::string childName)
	{
		std::vector<Transform*> childVector;

		if (entity && entity->GetName() == childName) 
			childVector.push_back(this);

		for (Transform* child : children) 
		{
			if (child) 
			{
				auto childResults = child->GetChildrenWithName(childName);
				childVector.insert(childVector.end(), childResults.begin(), childResults.end());
			}
		}

		return childVector;
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

glm::vec3 Mat4ToEuler(const glm::mat4& rotationMatrix)
{
	glm::vec3 euler;

	// Extraer componentes de rotación
	float sy = glm::sqrt(rotationMatrix[0][0] * rotationMatrix[0][0] + rotationMatrix[1][0] * rotationMatrix[1][0]);

	bool singular = sy < 1e-6; // Cerca de cero indica una singularidad

	if (!singular) {
		euler.x = glm::atan(rotationMatrix[2][1], rotationMatrix[2][2]); // Rotación en X
		euler.y = glm::atan(-rotationMatrix[2][0], sy);                  // Rotación en Y
		euler.z = glm::atan(rotationMatrix[1][0], rotationMatrix[0][0]); // Rotación en Z
	}
	else {
		euler.x = glm::atan(-rotationMatrix[1][2], rotationMatrix[1][1]); // Rotación en X
		euler.y = glm::atan(-rotationMatrix[2][0], sy);                   // Rotación en Y
		euler.z = 0;                                                      // Rotación en Z (indeterminado)
	}

	// Convertir a grados
	return glm::degrees(euler);
}
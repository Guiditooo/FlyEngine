#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Exports/Exports.h"

#include "TransformComponent/TransformComponent.h"

namespace FlyEngine
{
	namespace Entities
	{
		class Entity;
	}

	class FLY_API Transform
	{
	private:
		TransformComponent* worldTransform;
		TransformComponent* localTransform;

		std::vector<Transform*> children;
		Transform* parent;

		Entities::Entity* entity;

		void UpdateMatrices();
		void FreeLocalMatrix();

	public:
		Transform(Entities::Entity* entity = nullptr);
		~Transform();

		void SetWorldPosition(float x, float y, float z);
		void SetLocalPosition(float x, float y, float z);

		void SetWorldRotation(float x, float y, float z);
		void SetLocalRotation(float x, float y, float z);

		void SetWorldScale(float x, float y, float z);
		void SetLocalScale(float x, float y, float z);

		void WorldTranslate(float x, float y, float z);
		void LocalTranslate(float x, float y, float z);

		void WorldRotate(float x, float y, float z);
		void LocalRotate(float x, float y, float z);

		void WorldScale(float x, float y, float z);
		void LocalScale(float x, float y, float z);

		glm::vec3 GetWorldPosition();
		glm::vec3 GetLocalPosition();

		glm::vec3 GetWorldRotation();
		glm::vec3 GetLocalRotation();

		glm::vec3 GetWorldScale();
		glm::vec3 GetLocalScale();

		void UpdateLocalMatrix();
		void UpdateWorldMatrix();

		Transform* GetParent();
		std::vector<Transform*> GetChildren();

		void AddChild(Transform* newChild);
		void SetParent(Transform* newParent);

		void RemoveChild(Transform* child);
		void RemoveParent();
	
		void SetEntity(Entities::Entity* entity);

		Entities::Entity* GetEntity();
	};
}

#endif // !TRANSFORM_H
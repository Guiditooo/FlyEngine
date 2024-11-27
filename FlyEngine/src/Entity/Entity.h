#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <functional>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform/Transform.h"
#include "VertexAttribute/VertexAttribute.h"
#include "Exports/Exports.h"
#include "Buffers/Buffers.h"
#include "FlyFunctions/Color/Color.h"

#include "BoundingBox/BoundingBox.h"

namespace FlyEngine
{
	namespace Materials
	{
		class Material;
	}

	class Shader;

	namespace Entities
	{
		class FLY_API Entity
		{
		protected:
			std::vector<Utils::VertexAttribute> vertexAttributes;
			std::vector<unsigned int> index;
			std::vector<float> vertex;

			Utils::Buffers* buffers;

			bool active;
			bool activeInHierarchy;

			Materials::Material* material;

			Transform* transform;

			Utils::Color color;

			Utils::BoundingBox localBoundingBox;
			Utils::BoundingBox worldBoundingBox;

			bool settedAsCameraTarget = false;
			bool printModificationMessage;

			void CreateBaseEntity(std::string name);

			void PrintCreationMsg();

			std::string name;

			int indexCount;
			int vertexCount;
			int vertexSize;

		public:
			Entity(std::string name, Entity* parent = nullptr );
			Entity(std::string name, glm::vec3 pos, Entity* parent = nullptr);
			Entity(std::string name, glm::vec3 pos, glm::quat rot, Entity* parent = nullptr);
			Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale, Entity* parent = nullptr);
			~Entity();

			void SetActive(bool isActive);
			bool IsActive();

			bool IsActiveInHierarchy();

			void SetAsCameraTarget(bool value);
			bool IsCameraTarget();

			void SetName(std::string newName);

			void SetMaterial(Materials::Material* newMaterial, bool setRecursively);

			virtual void SetColor(Utils::Color newColor);
			virtual void SetColor(glm::vec3 newColor);
			virtual void SetColor(float r, float g, float b);
			virtual void SetColor(Utils::COLOR newColor);
			Utils::Color GetColor();
			glm::vec3 GetColorV3();

			glm::mat4 GetModelMatrix();

			//void SetPosition(float x, float y, float z);
			//void SetPosition(float x);
			//void SetPosition(glm::vec3 pos);

			//void SetRotation(float x, float y, float z);
			//void SetRotation(glm::vec3 rot);
			//void SetRotation(glm::quat rot);

			//void SetScale(float x, float y, float z);
			//void SetScale(glm::vec3 scale);
			//void SetScale(float scale);

			void SetBoundingBox(Utils::BoundingBox bounds);
			void SetBoundingBox(glm::vec3 min, glm::vec3 max);
			void SetBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

			void SetWorldBoundingBox(Utils::BoundingBox bounds);

			Utils::BoundingBox GetLocalBoundingBox();
			Utils::BoundingBox GetWorldBoundingBox();

			void AddChild(Entity* newChild);
			void SetParent(Entity* newParent);

			void RemoveChild(Entity* child);
			void RemoveParent();

			Entity* GetParent();
			Entity* GetRoot();
			std::vector<Entity*> GetChildren();
			std::vector<Entity*> GetChildrenWithName(std::string childName);

			void Traverse(const std::function<void(Entity*)>& action);

			Transform* GetTransform();
			//glm::mat4 GetWorldTransform();

			void MoveForward(float amount);
			void MoveBackward(float amount);
			void MoveLeft(float amount);
			void MoveRight(float amount);
			void MoveUp(float amount);
			void MoveDown(float amount);
			 
			Materials::Material* GetMaterial();
			Shader* GetShader();
			int GetShaderID();

			Utils::Buffers* GetBuffers();
			std::vector<Utils::VertexAttribute> GetVertexAttributes();

			std::vector<float> GetVertexList();
			std::vector<unsigned int> GetIndexList();

			int GetIndexCount();
			int GetVertexCount();
			int GetVertexSize();

			std::string GetName();

			void ToggleModificationMessage(bool isActive);

			void UseShader();

		};

	}
}
#endif // !ENTITY_H
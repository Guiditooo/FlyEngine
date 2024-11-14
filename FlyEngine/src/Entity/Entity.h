#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Transform/Transform.h"
#include "VertexAttribute/VertexAttribute.h"
#include "Exports/Exports.h"
#include "Buffers/Buffers.h"
#include "FlyFunctions/Color/Color.h"

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
			std::vector<Entity*> childs;
			std::vector<float> vertex;
			Entity* parent;

			Utils::Buffers* buffers;
			bool active;

			Materials::Material* material;

			Transform* transform;

			Utils::Color color;

			bool settedAsCameraTarget = false;
			bool printModificationMessage;

			void CreateBaseEntity(std::string name);

			void PrintCreationMsg();

			std::string name;

			int indexCount;
			int vertexCount;
			int vertexSize;

		public:
			Entity(std::string name);
			Entity(std::string name, glm::vec3 pos);
			Entity(std::string name, glm::vec3 pos, glm::quat rot);
			Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale);
			~Entity();

			void SetActive(bool isActive);
			bool IsActive();

			void SetAsCameraTarget(bool value);
			bool IsCameraTarget();

			void SetName(std::string newName);

			void SetMaterial(Materials::Material* newMaterial);

			virtual void SetColor(Utils::Color newColor);
			virtual void SetColor(glm::vec3 newColor);
			virtual void SetColor(float r, float g, float b);
			virtual void SetColor(Utils::COLOR newColor);
			Utils::Color GetColor();
			glm::vec3 GetColorV3();

			glm::mat4 GetModelMatrix();

			virtual void SetPosition(float x, float y, float z);
			virtual void SetPosition(float x);
			virtual void SetPosition(glm::vec3 pos);

			virtual void SetRotation(float x, float y, float z);
			virtual void SetRotation(glm::vec3 rot);
			virtual void SetRotation(glm::quat rot);

			virtual void SetScale(float x, float y, float z);
			virtual void SetScale(glm::vec3 scale);
			virtual void SetScale(float scale);

			void SetChild(Entity* newChild);
			void SetParent(Entity* newParent);

			Transform* GetTransform();

			Entity* GetParent();
			std::vector<Entity*> GetChilds();

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

			virtual void Draw() = 0;
		};

	}
}
#endif // !ENTITY_H
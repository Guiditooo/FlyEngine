#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VertexAttribute/VertexAttribute.h"
#include "Exports/Exports.h"
#include "Buffers/Buffers.h"
#include "Material/Material.h"
#include "FlyFunctions/Color/Color.h"

namespace FlyEngine
{

	namespace Entities
	{

		class FLY_API Entity
		{
		protected:
			std::vector<Utils::VertexAttribute> vertexAttributes;

			Utils::Buffer* buffers;
			bool active;

			Materials::Material* material;

			Utils::Color color;

			glm::mat4 translateMatrix;
			glm::mat4 rotationMatrix;
			glm::mat4 scaleMatrix;
			glm::mat4 modelMatrix;

			glm::vec3 positionVector;
			glm::vec3 rotationVector;
			glm::quat rotationQuaternion;
			glm::vec3 scaleVector;

			bool shouldUpdateModelMatrix = false;

			void CreateBaseEntity(std::string name);

			glm::quat EulerToQuat(glm::vec3 euler);
			glm::mat4 EulerToMat4(glm::vec3 euler);
			glm::vec3 Mat4ToEuler(glm::mat4 matrix);
			glm::vec3 QuaternionToEuler(glm::quat quat);
			glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
			glm::quat QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards);

			void PrintCreationMsg();

			bool printModificationMessage;

			std::string name;

			std::vector<float> vertex;
			std::vector<unsigned int> index;

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

			void SetName(std::string newName);

			void SetColor(Utils::Color newColor);
			void SetColor(glm::vec3 newColor);
			void SetColor(float r, float g, float b);
			void SetColor(Utils::COLOR newColor);
			Utils::Color GetColor();

			void UpdateModelMatrix();
			glm::mat4 GetModelMatrix();

			virtual void SetPosition(float x, float y, float z);
			virtual void SetRotation(float x, float y, float z);
			virtual void SetRotation(glm::quat rot);
			void SetScale(float x, float y, float z);

			glm::vec3 GetPosition();
			glm::vec3 GetRotation();
			glm::vec3 GetScale();

			glm::vec3 GetFront();
			glm::vec3 GetUp();
			glm::vec3 GetRight();

			void MoveForward(float amount);
			void MoveBackward(float amount);
			void MoveLeft(float amount);
			void MoveRight(float amount);
			void MoveUp(float amount);
			void MoveDown(float amount);

			virtual void Translate(float x, float y, float z);
			virtual void Rotate(float x, float y, float z);
			void Scale(float x, float y, float z);

			void SetMaterial(Materials::Material* newMaterial);
			void ApplyMaterial();
			Materials::Material* GetMaterial();

			Utils::Buffer* GetBuffers();
			std::vector<Utils::VertexAttribute> GetVertexAttributes();

			std::vector<float> GetVertexList();
			std::vector<unsigned int> GetIndexList();

			int GetIndexCount();
			int GetVertexCount();
			int GetVertexSize();

			std::string GetName();

			void ToggleModificationMessage(bool isActive);

			virtual void Draw() = 0;

		private: 
			glm::mat4 RotateInX(float angles);
			glm::mat4 RotateInY(float angles);
			glm::mat4 RotateInZ(float angles);
		};

	}
}
#endif // !ENTITY_H
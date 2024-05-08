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

			Utils::Buffer buffers;
			bool active;

			Material* material;

			Utils::Color color;

			glm::mat4 translateMatrix;
			glm::mat4 rotationMatrix;
			glm::mat4 scaleMatrix;
			glm::mat4 model;

			glm::vec3 positionVector;
			glm::vec3 rotationVector;
			glm::quat rotationQuaternion;
			glm::vec3 scaleVector;

			glm::quat EulerToQuat(glm::vec3 euler);
			glm::mat4 EulerToMat4(glm::vec3 euler);
			glm::vec3 QuaternionToEuler(glm::quat quat);
			glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
			glm::quat QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards);

			std::string name;

			int indexCount;
			int vertexCount;
			int vertexSize;

		public:
			Entity();
			~Entity();

			void SetActive(bool isActive);
			bool IsActive();

			void SetColor(Utils::Color newColor);
			void SetColor(glm::vec3 newColor);
			void SetColor(float r, float g, float b);
			void SetColor(Utils::COLOR newColor);
			Utils::Color GetColor();

			void UpdateModelMatrix();
			glm::mat4 GetModelMatrix();

			void SetPosition(float x, float y, float z);
			void SetRotation(float x, float y, float z);
			void SetScale(float x, float y, float z);

			glm::vec3 GetPosition();
			glm::vec3 GetRotation();
			glm::vec3 GetScale();

			void Translate(float x, float y, float z);
			void Rotate(float x, float y, float z);
			void Scale(float x, float y, float z);

			void SetMaterial(Material* newMaterial);
			void ApplyMaterial();
			Material* GetMaterial();

			Utils::Buffer GetBuffers();
			std::vector<Utils::VertexAttribute> GetVertexAttributes();

			int GetIndexCount();
			int GetVertexCount();
			int GetVertexSize();

			virtual void Draw() = 0;
		};

	}
}
#endif // !ENTITY_H
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Exports/Exports.h"

namespace FlyEngine
{
	class FLY_API Transform
	{
	public:

		Transform();
		~Transform();

		void SetPosition(float x, float y, float z);
		void SetPosition(float x);
		void SetPosition(glm::vec3 pos);

		void SetRotation(float x, float y, float z);
		void SetRotation(glm::vec3 rot);
		void SetRotation(glm::quat rot);

		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);
		void SetScale(float scale);

		void SetFront(glm::vec3 front);
		void SetUp(glm::vec3 up);
		void SetRight(glm::vec3 right);
	
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

		glm::vec3 GetFront();
		glm::vec3 GetUp();
		glm::vec3 GetRight();

		glm::mat4 GetModelMatrix();

		virtual void Translate(float x, float y, float z);
		virtual void Translate(glm::vec3 pos);

		virtual void RotateAround(float x, float y, float z);
		virtual void Rotate(float x, float y, float z);
		virtual void Rotate(glm::vec3 rot);

		virtual void WorldRotate(float x, float y, float z);
		virtual void WorldRotate(glm::vec3 rot);

		virtual void Scale(float x, float y, float z);
		virtual void Scale(glm::vec3 scale);
		virtual void Scale(float scale);

		void UpdateModelMatrix();

	private:
		glm::mat4 translateMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
		glm::mat4 modelMatrix;

		glm::vec3 positionVector;
		glm::vec3 rotationVector;
		glm::quat rotationQuaternion;
		glm::vec3 scaleVector;

		bool shouldUpdateModelMatrix;

		glm::quat EulerToQuat(glm::vec3 euler);
		glm::mat4 EulerToMat4(glm::vec3 euler);
		glm::vec3 Mat4ToEuler(glm::mat4 matrix);
		glm::vec3 QuaternionToEuler(glm::quat quat);
		glm::vec3 QuatToVec(glm::quat quat, glm::vec3 vec);
		glm::quat QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards);
	};
}

#endif // !TRANSFORM_H
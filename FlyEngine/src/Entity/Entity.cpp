#include <string>
#include <glm/gtx/euler_angles.hpp>

#include "Entity.h"
#include "Renderer/Renderer.h"
#include "FlyFunctions/Debugger/Debugger.h"

namespace FlyEngine
{
	namespace Entities
	{
		//www.c-jump.com/bcc/common/Talk3/Math/GLM/GLM.html#W01_0030_matrix_transformation
		const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
		const float pi = 3.14159265359f;

		Entity::Entity(std::string name)
		{
			CreateBaseEntity(name);
		}
		Entity::Entity(std::string name, glm::vec3 pos)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
		}
		Entity::Entity(std::string name, glm::vec3 pos, glm::quat rot, glm::vec3 scale)
		{
			CreateBaseEntity(name);
			SetPosition(pos.x, pos.y, pos.z);
			SetRotation(rot);
			SetScale(scale.x, scale.y, scale.z);
		}

		void Entity::CreateBaseEntity(std::string name)
		{
			this->name = name;

			modelMatrix = glm::mat4(1.0f);
			color = glm::vec3(1.0f);

			translateMatrix = glm::mat4(1.0f);
			rotationMatrix = glm::mat4(1.0f);
			scaleMatrix = glm::mat4(1.0f);

			positionVector = glm::vec3(0, 0, 0);
			rotationVector = glm::vec3(0, 0, 0);
			scaleVector = glm::vec3(1, 1, 1);

			rotationQuaternion = EulerToQuat(rotationVector);

			indexCount = 0;
			vertexCount = 0;
			vertexSize = 0;

			material = nullptr;
			buffers = new Utils::Buffer();
			active = true;
		}

		Entity::~Entity()
		{
		}

		glm::quat Entity::EulerToQuat(glm::vec3 euler)
		{
			euler *= deg2rad;

			float cy = cos(euler.z * 0.5f);
			float sy = sin(euler.z * 0.5f);
			float cp = cos(euler.x * 0.5f);
			float sp = sin(euler.x * 0.5f);
			float cr = cos(euler.y * 0.5f);
			float sr = sin(euler.y * 0.5f);

			glm::quat q;
			q.w = cr * cp * cy + sr * sp * sy;
			q.x = cr * sp * cy + sr * cp * sy;
			q.y = sr * cp * cy - cr * sp * sy;
			q.z = cr * cp * sy - sr * sp * cy;
			return q;
		}

		glm::mat4 Entity::EulerToMat4(glm::vec3 euler)
		{
			// Calculate rotation about x axis
			glm::mat4  R_x;
			R_x[0] = { 1, 0, 0, 0 };
			R_x[1] = { 0, cos(euler.x), -sin(euler.x), 0 };
			R_x[2] = { 0, sin(euler.x), cos(euler.x), 0 };
			R_x[3] = { 0, 0, 0, 1 };


			// Calculate rotation about y axis
			glm::mat4  R_y;
			R_y[0] = { cos(euler.y), 0, sin(euler.y), 0 };
			R_y[1] = { 0, 1, 0, 0 };
			R_y[2] = { -sin(euler.x), 0, cos(euler.x), 0 };
			R_y[3] = { 0, 0, 0, 1 };

			// Calculate rotation about z axis
			glm::mat4  R_z;
			R_z[0] = { cos(euler.y), -sin(euler.y), 0, 0 };
			R_z[1] = { sin(euler.x), cos(euler.x), 0, 0 };
			R_z[2] = { 0, 0, 1, 0 };
			R_z[3] = { 0, 0, 0, 1 };

			// Combined rotation matrix
			glm::mat4  R = R_z * R_y * R_x;

			return R;
		}

		glm::vec3 Entity::Mat4ToEuler(glm::mat4 matrix)
		{
			glm::vec3 euler;

			if (matrix[1][0] < 1.0f)
			{
				if (matrix[1][0] > -1.0f)
				{
					euler.y = asin(matrix[1][0]);
					euler.x = atan2(-matrix[1][2], matrix[1][1]);
					euler.z = atan2(-matrix[2][0], matrix[0][0]);
				}
				else
				{
					euler.y = -glm::half_pi<float>();
					euler.x = -atan2(matrix[2][1], matrix[2][2]);
					euler.z = 0.0f;
				}
			}
			else
			{
				euler.y = glm::half_pi<float>();
				euler.x = atan2(matrix[2][1], matrix[2][2]);
				euler.z = 0.0f;
			}

			return euler;
		}

		glm::vec3 Entity::QuaternionToEuler(glm::quat quat)
		{
			glm::vec3 angles;

			// Roll (x-axis rotation)
			float sinr_cosp = 2 * (quat.x * quat.y + quat.z * quat.w);
			float cosr_cosp = 1 - 2 * (quat.y * quat.y + quat.z * quat.z);
			angles.x = glm::atan(sinr_cosp, cosr_cosp);

			// Pitch (y-axis rotation)
			float sinp = 2 * (quat.x * quat.z - quat.w * quat.y);
			if (glm::abs(sinp) >= 1)
				angles.y = glm::pi<float>() / 2 * glm::sign(sinp); // Use 90 degrees if out of range
			else
				angles.y = glm::asin(sinp);

			// Yaw (z-axis rotation)
			float siny_cosp = 2 * (quat.x * quat.w + quat.y * quat.z);
			float cosy_cosp = 1 - 2 * (quat.z * quat.z + quat.w * quat.w);
			angles.z = glm::atan(siny_cosp, cosy_cosp);

			return angles;
		}

		glm::vec3 Entity::QuatToVec(glm::quat quat, glm::vec3 vec)
		{
			float x2 = quat.x * 2.f;
			float y2 = quat.y * 2.f;
			float z2 = quat.z * 2.f;
			float xx2 = quat.x * x2;
			float yy2 = quat.y * y2;
			float zz2 = quat.z * z2;
			float xy2 = quat.x * y2;
			float xz2 = quat.x * z2;
			float yz2 = quat.y * z2;
			float wx2 = quat.w * x2;
			float wy2 = quat.w * y2;
			float wz2 = quat.w * z2;

			glm::vec3 res;
			res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
			res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
			res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
			return res;
		}

		glm::quat Entity::QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards)
		{
			forward = glm::normalize(forward);
			glm::vec3 right = glm::normalize(glm::cross(upwards, forward));
			upwards = glm::cross(forward, right);

			float m00 = right.x;
			float m01 = right.y;
			float m02 = right.z;
			float m10 = upwards.x;
			float m11 = upwards.y;
			float m12 = upwards.z;
			float m20 = forward.x;
			float m21 = forward.y;
			float m22 = forward.z;

			float diagonal = m00 + m11 + m22;
			float qw = 0;
			float qx = 0;
			float qy = 0;
			float qz = 0;

			if (diagonal > 0)
			{
				float wComponent = glm::sqrt(diagonal + 1.0f) * 2;
				qw = 0.25f * wComponent;
				qx = (m21 - m12) / wComponent;
				qy = (m02 - m20) / wComponent;
				qz = (m10 - m01) / wComponent;
			}
			else if ((m00 > m11) && (m00 > m22))
			{
				float wComponent = glm::sqrt(1.0f + m00 - m11 - m22) * 2;
				qw = (m21 - m12) / wComponent;
				qx = 0.25f * wComponent;
				qy = (m01 + m10) / wComponent;
				qz = (m02 + m20) / wComponent;
			}
			else if (m11 > m22)
			{
				float wComponent = glm::sqrt(1.0f + m11 - m00 - m22) * 2;
				qw = (m02 - m20) / wComponent;
				qx = (m01 + m10) / wComponent;
				qy = 0.25f * wComponent;
				qz = (m12 + m21) / wComponent;
			}
			else
			{
				float wComponent = glm::sqrt(1.0f + m22 - m00 - m11) * 2;
				qw = (m10 - m01) / wComponent;
				qx = (m02 + m20) / wComponent;
				qy = (m12 + m21) / wComponent;
				qz = 0.25f * wComponent;
			}

			return glm::quat(qx, qy, qz, qw);
		}

		void Entity::SetActive(bool isActive)
		{
			std::string text = name;

			active = isActive;

			text += active ? " is Active!" : " is not Active!";

			Debugger::ConsoleMessage(&text[0]);
		}

		bool Entity::IsActive()
		{
			return active;
		}

		void Entity::SetName(std::string newName)
		{
			name = newName;
		}

		void Entity::PrintCreationMsg()
		{
			std::string text = "Created ";
			text += name;
			text += " successfully!";

			Debugger::ConsoleMessageID(&text[0]);
		}

		void Entity::SetColor(FlyEngine::Color newColor)
		{
			color = newColor;
		}

		void Entity::SetColor(glm::vec3 newColor)
		{
			color = Color(newColor);
		}

		void Entity::SetColor(float r, float g, float b)
		{
			color = Color(r, g, b);
		}

		void Entity::SetColor(FlyEngine::COLOR newColor)
		{
			color = Color(newColor);
		}

		Utils::Color Entity::GetColor()
		{
			return color;
		}

		void Entity::UpdateModelMatrix()
		{
			modelMatrix = translateMatrix * rotationMatrix * scaleMatrix;
			shouldUpdateModelMatrix = false;
		}

		glm::mat4 Entity::GetModelMatrix()
		{
			if (shouldUpdateModelMatrix)
				UpdateModelMatrix();
			return modelMatrix;
		}

		void Entity::SetPosition(float x, float y, float z)
		{
			positionVector = glm::vec3(x, y, z);
			translateMatrix = glm::translate(glm::mat4(1.0f), positionVector);
			shouldUpdateModelMatrix = true;

			if (printModificationMessage)
			{
				std::string text = "Setted Position of ";
				text += name;
				text += " successfully to ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}
		}

		void Entity::SetRotation(float x, float y, float z)
		{
			rotationVector = glm::vec3(x, y, z);
			rotationQuaternion = glm::quat(glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z)));
			rotationMatrix = glm::mat4_cast(rotationQuaternion);
			shouldUpdateModelMatrix = true;

			if (printModificationMessage)
			{
				std::string text = "Setted Rotation of ";
				text += name;
				text += " successfully ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}
		}

		void Entity::SetRotation(glm::quat rot)
		{
			rotationQuaternion = rot;
			rotationVector = glm::eulerAngles(rot);
			rotationMatrix = glm::mat4_cast(rotationQuaternion);
			shouldUpdateModelMatrix = true;

			if (printModificationMessage)
			{
				std::string text = "Setted Rotation of ";
				text += name;
				text += " successfully ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(rotationVector.x, rotationVector.y, rotationVector.z));
			}
		}

		void Entity::SetScale(float x, float y, float z)
		{
			scaleVector = glm::vec3(x, y, z);
			scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);
			shouldUpdateModelMatrix = true;

			if (printModificationMessage)
			{
				std::string text = "Setted Scale of ";
				text += name;
				text += ". Now its ";

				Debugger::ConsoleMessageID(&text[0], glm::vec3(x, y, z));
			}
		}

		glm::vec3 Entity::GetPosition()
		{
			return positionVector;
		}

		glm::vec3 Entity::GetRotation()
		{
			return rotationVector;
		}

		glm::vec3 Entity::GetScale()
		{
			return scaleVector;
		}

		glm::vec3 Entity::GetFront()
		{
			return -GetModelMatrix()[2];
		}

		glm::vec3 Entity::GetUp()
		{
			return GetModelMatrix()[1];
		}

		glm::vec3 Entity::GetRight()
		{
			return GetModelMatrix()[1];
		}

		void Entity::Translate(float x, float y, float z)
		{
			positionVector += glm::vec3(x, y, z);
			translateMatrix = glm::translate(glm::mat4(1.0f), positionVector);
			shouldUpdateModelMatrix = true;
		}

		void Entity::Rotate(float x, float y, float z)
		{
			glm::quat rotX = glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
			glm::quat rotY = glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
			glm::quat rotZ = glm::angleAxis(glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::quat rot = rotZ * rotY * rotX;
			rotationQuaternion = rot * rotationQuaternion;
			rotationVector = glm::eulerAngles(rotationQuaternion);
			rotationMatrix = glm::mat4_cast(rotationQuaternion);
			shouldUpdateModelMatrix = true;
		}

		void Entity::Scale(float x, float y, float z)
		{
			scaleVector *= glm::vec3(x, y, z);
			scaleMatrix = glm::scale(glm::mat4(1.0f), scaleVector);
			shouldUpdateModelMatrix = true;
		}

		void Entity::SetMaterial(Material* newMaterial)
		{
			material = newMaterial;
		}

		void Entity::ApplyMaterial()
		{
			if (material != nullptr)
				material->Apply();
		}

		Material* Entity::GetMaterial()
		{
			return material;
		}

		FlyEngine::Utils::Buffer* Entity::GetBuffers()
		{
			return buffers;
		}

		int Entity::GetIndexCount()
		{
			return indexCount;
		}

		void Entity::Draw()
		{
		}

		std::vector<VertexAttribute> Entity::GetVertexAttributes()
		{
			return vertexAttributes;
		}

		std::vector<float> Entity::GetVertexList()
		{
			return vertex;
		}

		std::vector<unsigned int> Entity::GetIndexList()
		{
			return index;
		}

		glm::mat4 Entity::RotateInX(float angles)
		{
			glm::mat4 mat = glm::mat4(0);

			mat[0][0] = 1;
			mat[3][3] = 1;

			mat[1][1] = cos(angles);
			mat[1][2] = -sin(angles);
			mat[2][1] = sin(angles);
			mat[2][2] = cos(angles);

			return mat;
		}

		void Entity::ToggleModificationMessage(bool isActive)
		{
			printModificationMessage = isActive;
		}

		glm::mat4 Entity::RotateInY(float angles)
		{
			glm::mat4 mat = glm::mat4(0);

			mat[1][1] = 1;
			mat[3][3] = 1;

			mat[0][0] = cos(angles);
			mat[0][2] = sin(angles);
			mat[2][0] = -sin(angles);
			mat[2][2] = cos(angles);

			return mat;
		}

		glm::mat4 Entity::RotateInZ(float angles)
		{
			glm::mat4 mat = glm::mat4(0);

			mat[2][2] = 1;
			mat[3][3] = 1;

			mat[0][0] = cos(angles);
			mat[0][1] = -sin(angles);
			mat[1][0] = sin(angles);
			mat[1][1] = cos(angles);

			return mat;
		}

		int Entity::GetVertexCount()
		{
			return vertexCount;
		}

		int Entity::GetVertexSize()
		{
			return vertexSize;
		}

	}

}
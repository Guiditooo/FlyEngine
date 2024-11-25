#include "TransformElement.h"

#include <glm/gtx/euler_angles.hpp>

const float deg2rad = (glm::pi<float>() * 2.0f) / 360.0f;
const float pi = 3.14159265359f;

namespace FlyEngine
{
	glm::quat TransformElement::EulerToQuat(glm::vec3 euler)
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

	glm::mat4 TransformElement::EulerToMat4(glm::vec3 euler)
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

	glm::vec3 TransformElement::Mat4ToEuler(glm::mat4 matrix)
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

	glm::vec3 TransformElement::QuaternionToEuler(glm::quat quat)
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

	glm::vec3 TransformElement::QuatToVec(glm::quat quat, glm::vec3 vec)
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

	glm::quat TransformElement::QuaternionLookRotation(glm::vec3 forward, glm::vec3 upwards)
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

}
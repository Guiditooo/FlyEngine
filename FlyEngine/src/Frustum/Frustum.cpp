#include "Frustum.h"
#include "Transform/Transform.h"
#include "glm/glm.hpp"

namespace FlyEngine
{
	namespace FlyFrustrum
	{

		Frustum Frustum::createFrustumFromCamera(Transform camT, float aspect, float fovY, float zNear, float zFar)
		{
			Frustum     frustum;
			const float halfVSide = zFar * tanf(fovY * .5f);
			const float halfHSide = halfVSide * aspect;
			const glm::vec3 frontMultFar = zFar * camT.GetFront();

			frustum.nearFace = Plane(camT.GetPosition() + zNear * camT.GetFront(), camT.GetFront());
			frustum.farFace = Plane(camT.GetPosition() + frontMultFar, -camT.GetFront());
			frustum.rightFace = Plane(camT.GetPosition(), glm::cross(frontMultFar - camT.GetRight() * halfHSide, camT.GetUp()));
			frustum.leftFace = Plane(camT.GetPosition(), glm::cross(camT.GetUp(), frontMultFar + camT.GetRight() * halfHSide));
			frustum.topFace = Plane(camT.GetPosition(), glm::cross(camT.GetRight(), frontMultFar - camT.GetUp() * halfVSide));
			frustum.bottomFace = Plane(camT.GetPosition(), glm::cross(frontMultFar + camT.GetUp() * halfVSide, camT.GetRight()));

			return frustum;
		}

	}
}
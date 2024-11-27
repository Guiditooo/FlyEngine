#ifndef BSP_MANAGER_H
#define BSP_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include <glm/vec3.hpp>

#include "Plane/Plane.h"

namespace FlyEngine
{
	namespace Utils
	{
		struct BoundingBox;
	}

	namespace Managers
	{
		enum class BSPType
		{
			AxisX,
			AxisY,
			AxisZ,
		};


		class FLY_API BSPManager
		{
		private:
			static bool isActive;
			static BSPType type;
			static std::unordered_map<int, Plane*> planes;
			static std::vector<int> ablePlanes;
			static std::vector<int> checkingPlanes;
			static bool IsPlaneAble(Plane* plane);
		public:
			static void InitializeManager();
			static void AddPlane(Plane* newPlane);
			static void Update(glm::vec3 cameraPos);
			static void ChangeType(BSPType newType);
			static void SetActive(bool state);

			static bool CheckInside(Utils::BoundingBox entity);
		};
	}
}

#endif // !BSP_MANAGER_H

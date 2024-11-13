#ifndef BSP_MANAGER_H
#define BSP_MANAGER_H

#include <iostream>
#include <vector>

#include <glm/vec3.hpp>

#include "Plane/Plane.h"


namespace FlyEngine
{

	namespace Managers
	{
		class FLY_API BSPManager
		{
		private:
			static std::vector<Plane*> planes;
		public:
			static void InitializeManager();
			static void AddPlane(Plane* newPlane);
			static void Update(glm::vec3 cameraPos);
			static bool CheckInside(glm::vec3 otherEntity);
		};
	}
}

#endif // !BSP_MANAGER_H

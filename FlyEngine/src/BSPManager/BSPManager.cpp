#include "BSPManager.h"
#include "glm/gtx/hash.hpp"

struct Vector3Hash
{
	std::size_t operator()(const glm::vec3& v) const
	{
		return std::hash<float>()(v.x) ^ std::hash<float>()(v.y) ^ std::hash<float>()(v.z);
	}
};

namespace FlyEngine
{
	namespace Managers
	{
		BSPType BSPManager::type = BSPType::AxisY;
		std::unordered_map<int, Plane*> BSPManager::planes;
		std::vector<int> BSPManager::ablePlanes;
		std::vector<int> BSPManager::checkingPlanes;

		bool BSPManager::IsPlaneAble(Plane* plane)
		{
			glm::vec3 normal = plane->GetNormal(); 

			double veryLowNumber = 1e-6;

			switch (type) 
			{
			case BSPType::AxisX:
				return (glm::abs(normal.x) < veryLowNumber) &&
					((glm::abs(normal.y - 1.0f) < veryLowNumber || glm::abs(normal.y + 1.0f) < veryLowNumber) ||
					 (glm::abs(normal.z - 1.0f) < veryLowNumber || glm::abs(normal.z + 1.0f) < veryLowNumber));

			case BSPType::AxisY:
				return (glm::abs(normal.y) < veryLowNumber) &&
					((glm::abs(normal.x - 1.0f) < veryLowNumber || glm::abs(normal.x + 1.0f) < veryLowNumber) ||
					 (glm::abs(normal.z - 1.0f) < veryLowNumber || glm::abs(normal.z + 1.0f) < veryLowNumber));

			case BSPType::AxisZ:
				return (glm::abs(normal.z) < veryLowNumber) &&
					((glm::abs(normal.x - 1.0f) < veryLowNumber || glm::abs(normal.x + 1.0f) < veryLowNumber) ||
					 (glm::abs(normal.y - 1.0f) < veryLowNumber || glm::abs(normal.y + 1.0f) < veryLowNumber));

			default:
				return false;
			}
		}

		void BSPManager::InitializeManager()
		{
			planes.clear();
			ablePlanes.clear();
			checkingPlanes.clear();
		}
		void BSPManager::AddPlane(Plane* newPlane)
		{
			int planeID = newPlane->GetID();

			planes[planeID] = newPlane;

			if (IsPlaneAble(newPlane))
			{
				ablePlanes.push_back(planeID);
			}
		}
		void BSPManager::Update(glm::vec3 cameraPos)
		{
			std::unordered_map<glm::vec3, Plane*, Vector3Hash> closestPlanes;

			for (int id : ablePlanes)
			{
				Plane* plane = planes[id];
				glm::vec3 normal = plane->GetNormal();

				float distanceToCamera = glm::abs(plane->GetDistanceToPoint(cameraPos));

				if (closestPlanes.find(normal) == closestPlanes.end() ||
					distanceToCamera < glm::abs(closestPlanes[normal]->GetDistanceToPoint(cameraPos)))
				{
					closestPlanes[normal] = plane;
				}
			}

			checkingPlanes.clear();
			for (const auto& entry : closestPlanes)
			{
				checkingPlanes.push_back(entry.second->GetID());
			}
		}
		void BSPManager::ChangeType(BSPType newType)
		{
			type = newType;
			ablePlanes.clear();

			for (const auto& [id, plane] : planes)
			{
				if (IsPlaneAble(plane))
				{
					ablePlanes.push_back(id);
				}
			}
		}
		bool BSPManager::CheckInside(glm::vec3 otherEntityPos)
		{
			for (int planeID : checkingPlanes)
			{
				Plane* plane = planes[planeID];
				if (!plane->IsPointInFront(otherEntityPos))
				{
					return false; // El punto está fuera del espacio definido por el plano
				}
			}
			return true;
		}
	}
}
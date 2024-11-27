#include "BSPManager.h"
#include "glm/gtx/hash.hpp"

#include "BoundingBox/BoundingBox.h"

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
		bool BSPManager::isActive;

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
			type = BSPType::AxisY;
			isActive = false;
		}
		void BSPManager::AddPlane(Plane* newPlane)
		{
			for (const auto& entry : planes)
			{
				const Plane* existingPlane = entry.second;

				if (newPlane->Equals(existingPlane))
				{
					return;
				}
			}

			int planeID = newPlane->GetID();
			planes[planeID] = newPlane;

			if (IsPlaneAble(newPlane))
			{
				ablePlanes.push_back(planeID);
			}
		}
		void BSPManager::Update(glm::vec3 cameraPos)
		{
			if (!isActive)
				return;

			std::unordered_map<glm::vec3, Plane*, Vector3Hash> closestPlanes;

			for (int id : ablePlanes)
			{
				Plane* plane = planes[id];
				glm::vec3 normal = plane->GetNormal();

				if (!IsPlaneAble(plane)) continue;

				float distanceToCamera = glm::abs(plane->GetDistanceToPoint(cameraPos));

				bool isNewPlane = true;
				for (auto& entry : closestPlanes)
				{
					if (glm::dot(glm::normalize(normal), glm::normalize(entry.first)) > 0.9999f)
					{
						if (distanceToCamera < glm::abs(entry.second->GetDistanceToPoint(cameraPos)))
						{
							entry.second = plane;
						}
						isNewPlane = false;
						break;
					}
				}

				if (isNewPlane)
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

		void BSPManager::SetActive(bool state)
		{
			isActive = state;
		}

		bool BSPManager::CheckInside(Utils::BoundingBox entity)
		{
			if (!isActive)
				return true;

			for (int planeID : checkingPlanes)
			{
				Plane* plane = planes[planeID];
				int pointsInFront = 0;

				glm::vec3 corners[8] = {
					entity.min,
					{entity.min.x, entity.min.y, entity.max.z},
					{entity.min.x, entity.max.y, entity.min.z},
					{entity.min.x, entity.max.y, entity.max.z},
					{entity.max.x, entity.min.y, entity.min.z},
					{entity.max.x, entity.min.y, entity.max.z},
					{entity.max.x, entity.max.y, entity.min.z},
					entity.max
				};

				for (const glm::vec3& corner : corners)
				{
					if (plane->IsPointInFront(corner))
					{
						pointsInFront++;
					}
				}

				if (pointsInFront == 0)
				{
					return false; // Auera de este plano.
				}
			}

			return true; // Está dentro de todos los planos.
		}
	}
}
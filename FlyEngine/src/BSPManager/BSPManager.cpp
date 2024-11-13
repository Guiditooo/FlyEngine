#include "BSPManager.h"


namespace FlyEngine
{
	namespace Managers
	{
		std::vector<Plane*> BSPManager::planes;
		
		void BSPManager::InitializeManager()
		{

		}
		void BSPManager::AddPlane(Plane* newPlane)
		{
			planes.push_back(newPlane);
		}
		void BSPManager::Update(glm::vec3 cameraPos)
		{
			//Si ta dentro, muestra, si no no :D
		}
		bool BSPManager::CheckInside(glm::vec3 otherEntity)
		{

		}
	}
}
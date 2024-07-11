#ifndef GAME_H
#define GAME_H

#include "FlyEngine.h"

using namespace FlyEngine;

namespace FlyGame
{

	enum class MovingObject
	{
		Cube,
		Camera,
		Light,
		Count
	};

	class Game : public BaseGame
	{
	private:
		CameraController* cameraController;
		
		Entities::Rectangle* rec;
		Entities::Rectangle* piso;
		Entities::Rectangle* pared1;
		Entities::Rectangle* pared2;
		
		Entities::Cube* box;
		Entities::Cube* box2;

		Texture* texture;

		Lights::PointLight* pointLight;
		Lights::PointLight* pointLightStatic;
		Lights::SpotLight* spotLight;

		Entities::Model* backpack;

		Entities::Model* barrel;
		Entities::Model* barrel2;
		Entities::Model* barrel3;

		Entities::Model* delorean;

		Entities::Model* ironGiant;

		Entities::Model* teapod;

		int aux = 0;

		MovingObject movingObject;

		Entities::Entity* movingEntity;


		void MoveObject(FlyEngine::Entities::Entity* entity, bool showMovement = true);
		void MoveObject(FlyEngine::Lights::Light* light, bool showMovement = true);

		void CheckForEnabling(KeyCode enableKey, KeyCode disableKey, Entities::Entity* thing);
		void CheckForEnabling(KeyCode enableKey, KeyCode disableKey, Lights::Light* light);
		void CheckForScaling(KeyCode maximizeKey, KeyCode minimizeKey, Entities::Entity* thing);
		void SetCameraTarget(Entities::Entity* target, CameraMode mode);

	public:
		Game(int width, int height, std::string name = "%NaN");
		~Game();

		void Init() override;
		void Update() override;
		void Deinit() override;
	};
}
#endif // !GAME_H
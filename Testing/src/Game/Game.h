#ifndef GAME_H
#define GAME_H

#include "FlyEngine.h"

using namespace FlyEngine;

namespace FlyGame
{

	enum class MovingObject
	{
		Player,
		Cube,
		Camera,
		Light,
		Count
	};

	class Game : public BaseGame
	{
	private:
		CameraController* cameraController;
		
		Entities::Rectangle* piso;
		Entities::Triangle* triangle;

		Entities::Cube* cube;

		Entities::Model* scene1;
		Entities::Model* scene2;
		Entities::Model* scene3;
		Entities::Model* robot;
		Entities::Model* silla;
		Entities::Model* bp;

		Entities::Model* cubos;

		//Entities::Model* scene;
		//Entities::Model* scene;

		Texture* texture;

		Lights::PointLight* pointLight;
		Lights::PointLight* pointLightStatic;
		Lights::SpotLight* spotLight;

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
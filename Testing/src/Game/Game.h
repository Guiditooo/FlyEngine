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
		
		Entities::Cube* player;
		Entities::Cube* cube;
		Entities::Cube* light;

		Texture* texture;

		Lights::PointLight* pointLight;
		Lights::PointLight* pointLightStatic;
		Lights::SpotLight* spotLight;

		Entities::Model* model;
		Entities::Model* model2;

		int aux = 0;

		MovingObject movingObject;

		Materials::Material* boxMat;

		void MoveObject(FlyEngine::Entities::Entity* entity, bool showMovement = true);
		void MoveObject(FlyEngine::Lights::Light* light, bool showMovement = true);

		void CheckForEnabling(KeyCode enableKey, KeyCode disableKey, Entities::Entity* thing);

	public:
		Game(int width, int height, std::string name);
		Game(int width, int height);
		~Game();

		void Init() override;
		void Update() override;
		void Deinit() override;
	};
}
#endif // !GAME_H
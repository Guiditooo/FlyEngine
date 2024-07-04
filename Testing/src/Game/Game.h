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
		
		Entities::Cube* player;
		Entities::Cube* cube;
		Entities::Cube* light;

		Texture* texture;

		int aux = 0;

		MovingObject movingObject;

		void MoveObject(FlyEngine::Entities::Entity* entity, bool showMovement = true);

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
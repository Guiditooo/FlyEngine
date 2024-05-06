#ifndef GAME_H
#define GAME_H

#include "FlyEngine.h"

using namespace FlyEngine;

namespace FlyGame
{
	class Game : public BaseGame
	{
	private:
		Camera* mainCamera;

		//Entities::Rectangle* rec = nullptr;
		Entities::Cube* cube = nullptr;
		int aux = 0;
		Utils::Input input;

	public:
		Game(int width, int height, std::string name);
		Game(int width, int height);
		~Game();

		Camera* GetMainCamera();

		void Init() override;
		void Update() override;
		void Deinit() override;
	};
}
#endif // !GAME_H
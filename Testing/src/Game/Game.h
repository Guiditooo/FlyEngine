#ifndef GAME_H
#define GAME_H

#include "FlyEngine.h"

using namespace FlyEngine;

namespace FlyGame
{

	class Game : public BaseGame
	{
	private:
		int winWidth = 800;
		int winHeight = 600;
		std::string gameName = "NaN%";

		Entities::Rectangle* rec = nullptr;
		int aux = 0;

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
#include <iostream>

#include "Game/Game.h"

using namespace FlyGame;

void main()
{
	Game* game = new Game(800, 600, "Testing Environment");
	game->RunGame();
	delete game;
}

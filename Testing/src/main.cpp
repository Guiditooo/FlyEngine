#include <iostream>

#include "Game/Game.h"
#include <time.h>

using namespace FlyGame;

void main()
{
	srand(time(NULL));
	
	Game* game = new Game(1000, 800, "Testing Environment");
	game->RunGame(); 
	
	if (game != nullptr)
		delete game;
	game = nullptr;
}
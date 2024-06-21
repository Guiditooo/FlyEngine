#include <iostream>

#include "Game/Game.h"
#include <time.h>

using namespace FlyGame;

void main()
{
	srand(time(NULL));
	
	Game* game = new Game(800, 600, "Testing Environment");
	game->RunGame();
	delete game;
	
}


#include <iostream>
#include <cstdlib>

#include "SDL2_Common.h"
#include "Game.hpp"

int main(int argc, char** argv)
{
	std::shared_ptr<Game> game = Game::instance();

	game->init();
	game->runGameLoop();

	exit(EXIT_SUCCESS);
}
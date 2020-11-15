#include <iostream>
#include "SDL.h"

#include "Game.h"

Game* game = nullptr;

int main(int argc, char * argv[]) {

	game = new Game();

	game->init(Game::GAME_TITLE, 0, 0, 800, 500);

	while (game->running()) {
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();
	return 0;
}
#pragma once
#include "GameState.h"

/*level pro souboje mezi dvouma hraci na jedne klavesnici*/

class ArenaMulti : public GameState
{
private:
	Player * player;
	Player * player2;

	StateBars * statebar;
	StateBars * statebar2;

	Button * menu;

public:
	ArenaMulti() {
		background = TextureManager::LoadTexture("Assets/enviroment/bg1.png");

		player = new Player("Assets/Player1.png", 1, 0, 200);
		player2 = new Player("Assets/Player2.png", 0, 500, 200);

		player->setTarget(player2);
		player2->setTarget(player);

		//gui
		statebar = new StateBars(100, 50);
		statebar->setFighter(player);
		statebar2 = new StateBars(600, 50);
		statebar2->setFighter(player2);

		menu = new Button(0, 0, "Pause");
		initInGameMenu();
	}
	
	//pri nacteni
	void onLoad() {
		player->onLoad();
		player2->onLoad();
		refresh = false;
	}

	void update() {
		if (refresh)
			onLoad();

		handle_events();

		if (!pause) {
			player->update();
			player2->update();

			statebar->update();
			statebar2->update();
		}
		

		menu->update();
		updateInGameMenu();
	}

	void render() {
		SDL_RenderCopy(Game::renderer, background, NULL, NULL);

		fightersRender(player, player2);

		statebar->render();
		statebar2->render();

		menu->render();
		renderInGameMenu();
	}

	void handle_events() {
		eventsInGameMenu();

		if (menu->clicked())
			pause = true;
	}
};

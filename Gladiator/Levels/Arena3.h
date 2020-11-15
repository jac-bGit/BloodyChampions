#pragma once
#include "GameState.h"

#include <iostream>

/*arena - treti stupen - u vody*/


class Arena3 : public GameState
{
private:
	Player * player;
	Enemy * enemy;

	StateBars * statebar;
	StateBars * statebar2;

	Button * menu;
	SDL_Texture * foreground;

public:
	Arena3() {
		background = TextureManager::LoadTexture("Assets/enviroment/bg3.png");
		foreground = TextureManager::LoadTexture("Assets/enviroment/fg3.png");

		player = new Player("Assets/Player1.png", 1, 0, 0);
		enemy = new Enemy("Assets/fighters/fighter3.png", "Assets/fighters/sword3.png", "Assets/fighters/shield3.png", player);

		player->setTarget(enemy);

		//gui
		statebar = new StateBars(100, 50);
		statebar->setFighter(player);
		statebar2 = new StateBars(600, 50);
		statebar2->setFighter(enemy);

		menu = new Button(0, 0, "Pause");
		initInGameMenu();
	}

	//pri nacteni levelu
	void onLoad() {
		//hrac
		player->onLoad();

		//oponent
		enemy->setAbilities(100, 3);
		enemy->setFightingAbs(12, 60, 2 * 60);
		enemy->setBlockingAbs(6, 45,  90, 2 * 60 + 30);
		enemy->setStaminaAbs(100, 0.3f, 0.6f);
		enemy->onLoad();

		refresh = false;
	}


	void update() {

		//pri vstupu do levelu
		if (refresh)
			onLoad();

		handle_events();

		if (!pause) {
			player->update();
			enemy->update();

			statebar->update();
			statebar2->update();
		}

		menu->update();
		updateInGameMenu();
		defeatMenu(player);
	}

	void render() {
		SDL_RenderCopy(Game::renderer, background, NULL, NULL);

		fightersRender(player, enemy);

		SDL_RenderCopy(Game::renderer, foreground, NULL, NULL);

		statebar->render();
		statebar2->render();

		menu->render();
		renderInGameMenu();
	}

	void handle_events() {
		eventsInGameMenu();

		if (menu->clicked()) {
			pause = true;
		}

		//viteztvi
		if (enemy->getHp() <= 0) {
			refresh = true;
			Game::arenaLevel = 4;
			Game::gamestate = 2; //arenaLobby
		}
	}
};
#pragma once
#include "GameState.h"

#include <iostream>

/*arena - 5. stupen - ledova jeskyne*/


class Arena5 : public GameState
{
private:
	Player * player;
	Enemy * enemy;

	StateBars * statebar;
	StateBars * statebar2;

	Button * menu;

public:
	Arena5() {
		background = TextureManager::LoadTexture("Assets/enviroment/bg5.png");

		player = new Player("Assets/Player1.png", 1, 0, 0);
		enemy = new Enemy("Assets/fighters/fighter6.png", "Assets/fighters/sword4.png", "Assets/fighters/shield4.png", player);

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
		enemy->setAbilities(120, 3);
		enemy->setFightingAbs(15, 30, 70);
		enemy->setBlockingAbs(7, 30, 60, 90);
		enemy->setStaminaAbs(140, 0.3f, 0.6f);
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
			Game::arenaLevel = 6;
			Game::gamestate = 2; //arenaLobby
		}
	}
};


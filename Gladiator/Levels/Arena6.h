#pragma once
#include "GameState.h"

#include <iostream>

/*arena - 6. stupen - japosnka zahrada*/


class Arena6 : public GameState
{
private:
	Player * player;
	Enemy * enemy;

	StateBars * statebar;
	StateBars * statebar2;

	Button * menu;
	SDL_Texture * foreground;

public:
	Arena6() {
		background = TextureManager::LoadTexture("Assets/enviroment/bg6.png");
		foreground = TextureManager::LoadTexture("Assets/enviroment/fg6.png");

		player = new Player("Assets/Player1.png", 1, 0, 0);
		enemy = new Enemy("Assets/fighters/fighter7.png", "Assets/fighters/sword7.png", "Assets/fighters/shield7.png", player);

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
		enemy->setAbilities(130, 3);
		enemy->setFightingAbs(18, 30, 60);
		enemy->setBlockingAbs(7, 30, 60, 90);
		enemy->setStaminaAbs(175, 0.3f, 0.6f);
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
			Game::arenaLevel = 7;
			Game::gamestate = 2; //arenaLobby
		}
	}
};


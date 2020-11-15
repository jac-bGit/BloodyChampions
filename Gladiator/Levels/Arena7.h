#pragma once
#include "GameState.h"

#include <iostream>

/*arena - 7. stupen - nekonecny vesmir*/


class Arena7 : public GameState
{
private:
	Player * player;
	Enemy * enemy;

	StateBars * statebar;
	StateBars * statebar2;

	Button * menu;

public:
	Arena7() {
		background = TextureManager::LoadTexture("Assets/enviroment/bg7.png");

		player = new Player("Assets/Player1.png", 1, 0, 0);
		enemy = new Enemy("Assets/fighters/fighter8.png", "Assets/sword1.png", "Assets/shield1.png", player);

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
		enemy->setAbilities(150, 3);
		enemy->setFightingAbs(20, 15, 60);
		enemy->setBlockingAbs(8, 15, 30, 60);
		enemy->setStaminaAbs(200, 0.25f, 0.5f);
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
			Game::gamestate = 10; //final
		}
	}
};


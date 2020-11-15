#pragma once
#include "GameState.h"

#include <iostream>

/*arena - prvni stupen - souboj proti slabemu AI*/


class WinLevel : public GameState
{
private:
	Button * menu;

public:
	WinLevel() {
		background = TextureManager::LoadTexture("Assets/enviroment/bgFinal.png");


		menu = new Button(10, 450, "Menu");
	}

	void update() {

		handle_events();
		menu->update();
	}

	void render() {
		SDL_RenderCopy(Game::renderer, background, NULL, NULL);

		menu->render();
	}

	void handle_events() {

		if (menu->clicked()) {
			Game::gamestate = 0;
		}
	}
};
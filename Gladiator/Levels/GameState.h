#pragma once
#include "../Game.h"
#include "../GameObject.h"


class GameState 
{
public:
	virtual void onLoad() {}; // do teto funkce se zapisou udalosti, ktere se stanou pri nacteni levelu (zmena stavu)
	virtual void handle_events() {};
	virtual void update() {};
	virtual void render() {};

	int stateID;
	int nextState;

	//obnoveni levelu
	bool refresh = true;

	GameState *currentState = nullptr;
	SDL_Texture * background;



	//prekryvani bojovniku podle vysky
	void fightersRender(Fighter * fighter1, Fighter * fighter2) {
		if (fighter1->body->y() > fighter2->body->y()) {
			fighter2->render();
			fighter1->render();
		}
		else {
			fighter1->render();
			fighter2->render();
		}
	}

	//in game menus
	Text * pauseText;
	Button * resume;
	Button * restart;
	Button * toMenu;

	bool pause = false;

	//defeat menu
	bool defeat = false;
	Text * defeatText;
	Button * again;
	Button * toArenaLobby;

	void initInGameMenu() {
		pauseText = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 30, "Pause", { 0, 0, 0 });
		resume = new Button(325, 200, "Resume");
		restart = new Button(325, 250, "Restart");
		toMenu = new Button(325, 300, "Menu");

		defeatText = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 30, "Defeat", { 0, 0, 0 });
		again = new Button(240, 200, "Try again");
		toArenaLobby = new Button(410, 200, "Arena lobby");
	}
	void updateInGameMenu() {
		if (pause && !defeat) {
			resume->update();
			restart->update();
			toMenu->update();
		}
		if (defeat) {
			again->update();
			toArenaLobby->update();
		}

	}

	void defeatMenu(Fighter * player) {
		if (player->getHp() <= 0)
			defeat = true;
		else
			defeat = false;
	}

	void renderInGameMenu() {
		if (pause && !defeat) {
			pauseText->render(360, 150);
			resume->render();
			restart->render();
			toMenu->render();
		}
		if (defeat) {
			defeatText->render(360, 150);
			again->render();
			toArenaLobby->render();
		}
	}

	void eventsInGameMenu() {
		const Uint8 * state = SDL_GetKeyboardState(NULL);

		if (!pause) {
			if (Game::myEvent.type == SDL_KEYDOWN) {
				if (state[SDL_SCANCODE_ESCAPE]) {
					pause = true;
				}
			}
		}
		if (pause && !defeat) {
			if (resume->clicked()) {
				pause = false;
			}

			if (restart->clicked()) {
				refresh = true;
				pause = false;
			}			

			if (toMenu->clicked()) {
				pause = false;
				Game::gamestate = 0;
				refresh = true;
			}

		}

		//porazka
		if (defeat) {
			if (again->clicked()) {
				refresh = true;
				pause = false;
				defeat = false;
			}

			if (toArenaLobby->clicked()) {
				refresh = true;
				defeat = false;
				//Game::arenaLevel = 2;
				Game::gamestate = 2; //arenaLobby
			}
		}
	}

};
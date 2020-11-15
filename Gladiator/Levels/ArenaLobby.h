#pragma once

#include "GameState.h"
#include "../Text.h"
#include <array>

class ArenaLobby : public GameState
{
private:
	Text * header;
	Button * toArena;
	Button * surrender;
	Button * backToMenu;

	SDL_Texture * thumbnail[7];

	//surrender restart postupu
	std::string surrenderStr = "Are you sure? You will lose all your progress.";
	bool wantSurrender = false;
	Text * surrenderTxt;
	Button * yes;
	Button * no;

public:
	ArenaLobby() {
		background = TextureManager::LoadTexture("Assets/menubg.png");
		//nahledove obrazky
		thumbnail[0] = TextureManager::LoadTexture("Assets/enviroment/bg1.png");
		thumbnail[1] = TextureManager::LoadTexture("Assets/enviroment/bg2.png");
		thumbnail[2] = TextureManager::LoadTexture("Assets/enviroment/thumbnail3.png");
		thumbnail[3] = TextureManager::LoadTexture("Assets/enviroment/thumbnail4.png");
		thumbnail[4] = TextureManager::LoadTexture("Assets/enviroment/bg5.png");
		thumbnail[5] = TextureManager::LoadTexture("Assets/enviroment/thumbnail6.png");
		thumbnail[6] = TextureManager::LoadTexture("Assets/enviroment/bg7.png");



		backToMenu = new Button(150, 400, "Menu");
		surrender = new Button(325, 400, "Surrender");
		toArena = new Button(500, 400, "Fight!");

		//surrender
		surrenderTxt = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, surrenderStr.c_str(), { 0, 0, 0 });
		yes = new Button(225, 250, "Yes");
		no = new Button(400, 250, "No");
	}

	void update() {
		handle_events();

		backToMenu->update();
		surrender->update();
		toArena->update();

		updateSurrender();
	}

	void render() {

		switch (Game::arenaLevel)
		{
		default:
			//SDL_RenderCopy(Game::renderer, background, NULL, NULL);
			SDL_RenderCopy(Game::renderer, thumbnail[Game::arenaLevel - 1], NULL, NULL);
			break;
		}

		toArena->render();
		surrender->render();
		backToMenu->render();

		renderSurrender();

	}


	void handle_events() {
		//zpet do menu, ale zachovat aktualni postup v soubojich
		if (backToMenu->clicked()) {
			Game::gamestate = 0;
		}

		//vratit se do menu a restartuje souboje
		if (surrender->clicked() && Game::arenaLevel > 1) {
			wantSurrender = true;
		}

		/*switch (Game::arenaLevel)
		{
		case 1:
			if (toArena->clicked())
				Game::gamestate = 3; //arena1
			break;
		case 2:
			if (toArena->clicked())
				Game::gamestate = 4; //arena2
			break;
		case 3:
			if (toArena->clicked())
				Game::gamestate = 5; //arena3
			break;
		case 4:
			if (toArena->clicked())
				Game::gamestate = 6; //arena4
			break;
		case 5:
			if (toArena->clicked())
				Game::gamestate = 7; //arena5
			break;
		case 6:
			if (toArena->clicked())
				Game::gamestate = 8; //arena6
			break;
		case 7:
			if (toArena->clicked())
				Game::gamestate = 9; //arena7
			break;
		}*/

		if (toArena->clicked())
			Game::gamestate = Game::arenaLevel + 2; 
	}




	//surrender
	void updateSurrender() {
		//update
		if (wantSurrender) {
			yes->update();
			no->update();

			//vyber moznosti
			if (yes->clicked()) {
				wantSurrender = false;
				Game::arenaLevel = 1;
			}

			if (no->clicked()) {
				wantSurrender = false;
			}
		}


	}

	//render
	void renderSurrender() {
		if (wantSurrender) {
			surrenderTxt->render(180, 200);
			yes->render();
			no->render();
		}
	}


};

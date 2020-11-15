#pragma once

#include "GameState.h"
#include "../Text.h"
#include <array>

class MainMenu : public GameState
{
private:
	int menuState = 0;

	Text * header;
	Button * toArena1;
	Button * toArenaMulti;
	Button * toControlls;
	Button * backToMenu;
	Button* btn_quit;

	Text * madeBy;

	//controlls
	std::string instructions[8] = {
		"Movement: pl1-WASD | pl2-arrow keys",
		" - stamina regeneration is slower when you move",
		"Attack: pl1-F | pl2-L",
		" - attack take 15 stamina a deal 10 dmg",
		"Block: pl1-G | pl2-K",
		" - you can block opponent attacks, but your stamina will stop regenerate",
		"Shield break: pl1-G -> F | pl2-K -> L  (hold block then attack)",
		" - disable opponent blocking for 3 seconds"
	};
	Text * controllsTxt[8];

public:
	MainMenu() {
		background = TextureManager::LoadTexture("Assets/menubg.png");

		header = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 30, "Bloody Champions", { 0, 0, 0 });
		toArena1 = new Button(150, 200, "Arena");
		toArenaMulti = new Button(150, 250, "Multiplayer");
		toControlls = new Button(150, 300, "Controls");
		btn_quit = new Button(150, 350, "Quit");
		backToMenu = new Button(50, 400, "Back");

		madeBy = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, "Made by: J. Werner", { 0,0,0 });

		//controlls
		/*for (int i = 0; i < sizeof(controllsTxt); i++) {
			controllsTxt[i] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[i].c_str(), { 0,0,0 });
		}*/
		controllsTxt[0] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[0].c_str(), { 0,0,0 });
		controllsTxt[1] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[1].c_str(), { 0,0,0 });
		controllsTxt[2] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[2].c_str(), { 0,0,0 });
		controllsTxt[3] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[3].c_str(), { 0,0,0 });
		controllsTxt[4] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[4].c_str(), { 0,0,0 });
		controllsTxt[5] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[5].c_str(), { 0,0,0 });
		controllsTxt[6] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[6].c_str(), { 0,0,0 });
		controllsTxt[7] = new Text("Assets/fonts/TheanoDidot-Regular.ttf", 20, instructions[7].c_str(), { 0,0,0 });
	}

	void update() {
		handle_events();

		switch (menuState)
		{
		case 0:
			toArena1->update();
			toArenaMulti->update();
			toControlls->update();
			btn_quit->update();
			break;
		case 1:
			backToMenu->update();
			break;
		}
	}

	void render() {
		SDL_RenderCopy(Game::renderer, background, NULL, NULL);

		switch (menuState)
		{
		case 0:
			header->render(125, 150);
			toArena1->render();
			toArenaMulti->render();
			toControlls->render();
			btn_quit->render();
			madeBy->render(550, 450);
			break;
		case 1:
			backToMenu->render();
			controllsTxt[0]->render(100, 100);
			controllsTxt[1]->render(100, 125);
			controllsTxt[2]->render(100, 160);
			controllsTxt[3]->render(100, 185);
			controllsTxt[4]->render(100, 220);
			controllsTxt[5]->render(100, 245);
			controllsTxt[6]->render(100, 280);
			controllsTxt[7]->render(100, 305);
			break;
		}
	}


	void handle_events() {

		switch (menuState)
		{
		case 0:
			if (toArena1->clicked())
				Game::gamestate = 2;

			if (toArenaMulti->clicked())
				Game::gamestate = 1;

			if (toControlls->clicked())
				menuState = 1;

			/*if (btn_quit->clicked())
				Game::clean();*/
			break;
		case 1:
			if (backToMenu->clicked())
				menuState = 0;
			break;
		}
	}


};
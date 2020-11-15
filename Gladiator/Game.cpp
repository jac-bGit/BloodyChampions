#include <iostream>

#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Levels/GameState.h"

//levely
#include "Levels/MainMenu.h"
#include "Levels/ArenaMulti.h"
#include "Levels/ArenaLobby.h"
#include "Levels/Arena1.h"
#include "Levels/Arena2.h"
#include "Levels/Arena3.h"
#include "Levels/Arena4.h"
#include "Levels/Arena5.h"
#include "Levels/Arena6.h"
#include "Levels/Arena7.h"
#include "Levels/WinLevel.h"

SDL_Renderer * Game::renderer = nullptr;
SDL_Event Game::myEvent;
bool Game::mouseClicked = false;

int Game::gamestate = 0;
int Game::arenaLevel = 1;

char* Game::GAME_TITLE = "Bloody Champions";

//levely
GameState * mainMenu;//0
GameState * multi;//1
GameState * arenaLobby;//2
GameState * arena1;//3
GameState * arena2;//4
GameState * arena3;//5
GameState * arena4;//6
GameState * arena5;//7
GameState * arena6;//8
GameState * arena7;//9
GameState * winLevel;//9

using namespace std;

Game::Game() {}

//inicializace SDL a vytvoreni okna
void Game::init(const char * title, int xpos, int ypos, int w, int h) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, 0);
	//int full = SDL_SetWindowFullscreen(window, 0);

	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 100, 0, 0, 255);

	isRunnig = true;

    //levely / stavy hry
	mainMenu = new MainMenu();
	multi = new ArenaMulti();
	arenaLobby = new ArenaLobby();
	arena1 = new Arena1();
	arena2 = new Arena2();
	arena3 = new Arena3();
	arena4 = new Arena4();
	arena5 = new Arena5();
	arena6 = new Arena6();
	arena7 = new Arena7();
	winLevel = new WinLevel();
}

//update - obnovuje akce programu
void Game::update() {


	switch (gamestate) {
	case 0:
		mainMenu->update();
		break;
	case 1:
		multi->update();
		break;
	case 2:
		arenaLobby->update();
		break;
	case 3:
		arena1->update();
		break;
	case 4:
		arena2->update();
		break;
	case 5:
		arena3->update();
		break;
	case 6:
		arena4->update();
		break;
	case 7:
		arena5->update();
		break;
	case 8:
		arena6->update();
		break;
	case 9:
		arena7->update();
		break;
	case 10:
		winLevel->update();
		break;
	}

}

//rendering - vykreslovani hry 
void Game::render() {
	SDL_RenderClear(renderer);

	switch (gamestate) {
	case 0:
		mainMenu->render();
		break;
	case 1:
		multi->render();
		break;
	case 2:
		arenaLobby->render();
		break;
	case 3:
		arena1->render();
		break;
	case 4:
		arena2->render();
		break;
	case 5:
		arena3->render();
		break;
	case 6:
		arena4->render();
		break;
	case 7:
		arena5->render();
		break;
	case 8:
		arena6->render();
		break;
	case 9:
		arena7->render();
		break;
	case 10:
		winLevel->render();
		break;
	}

	SDL_RenderPresent(renderer);
}

//game loop - obnovuje ve smycce okno hry dokud neni hra ukoncena 
void Game::handleEvents() {

	SDL_PollEvent(&myEvent);

	Uint32 starting_ticks = SDL_GetTicks();
	framerate(starting_ticks);

	switch (myEvent.type)
	{
	case SDL_QUIT:
		isRunnig = false;
		break;
	default:
		isRunnig = true;
		break;
	}
}

//ukonceni hry
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

//omezeni fps
void Game::framerate(Uint32 tick) {
	if ((1000 / fps) > SDL_GetTicks() - tick) {
		SDL_Delay(1000 / fps - (SDL_GetTicks() - tick));
	}
}

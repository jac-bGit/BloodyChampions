#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"

class GameObject;
class Player;

class Game 
{
public:
	static SDL_Renderer* renderer; //renderer slouzi pro vykreslovani objektu
	static SDL_Event myEvent; //vstupy od uzivatele do programu 
	static bool mouseClicked;

	static int arenaLevel;
	static char* Game::GAME_TITLE;

	Game();
	~Game();

	//vytvoreni okna
	void init(const char * title, int xpos, int ypos, int w, int h);

	//obnovovani a manipulace
	void handleEvents();
	void update();
	void render();
	void framerate(Uint32 tick);
	int getFps() { return fps; }

	//vrati jestli program bezi
	bool running() { return isRunnig; };

	void twoPlayers(Player * pl1, Player * pl2);
	bool targSetting = true;

	//levely
	static int gamestate;
	//vector<GameState> 

	//ukonceni
	void clean();
	static void endGame();

private:
	bool isRunnig;
	SDL_Window * window;

	const int fps = 60;

};

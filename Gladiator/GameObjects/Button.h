#pragma once
#include "../GameObject.h"
#include "../Game.h"
#include "../Text.h"
#include <string>

//class GameObject;

class Button 
{
public:
	Button(int x, int y, const char * labelText);
	//zakladni
	void update();
	void render();

	bool clicked();

private:
	SDL_Event butEvent;
	GameObject * go;
	Text * label;
};
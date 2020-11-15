#pragma once

#pragma once
#include "../TextureManager.h"


class GameObject
{
public:
	GameObject();
	GameObject(const char * filename, int x, int y, float scale);
	void getTexture(const char * filename, int x, int y, float scale);

	void update();
	void render();

	//manipulace s pozici hrace
	void setX(int x) { xpos = x; }
	void setY(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y; }
	//vraceni pozice
	int x() { return xpos; }
	int y() { return ypos; }


	void movement();

private:
	int xpos;
	int ypos;

	SDL_Texture * tex;
	SDL_Rect srcRect, destRect;

	//int speed = 2;
};
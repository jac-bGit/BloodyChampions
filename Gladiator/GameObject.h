#pragma once
#include "TextureManager.h"

//pridane objekty
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/StateBars.h"
#include "GameObjects/Button.h"

class GameObject 
{
public:
	GameObject();
	GameObject(const char * filename, int x, int y, float scale);
	GameObject(const char * filename, int x, int y, int w, int h, float scale);
	//void getTexture(const char * filename, int x, int y, float scale);

	//zakladni funkce
	void update();
	void render();

	//manipulace s pozici objektu
	void setX(int x) { xpos = x; }
	void setY(int y) { ypos = y; }
	void setPos(int x, int y) { xpos = x; ypos = y;}
	//vraceni pozice
	int x() { return xpos; }
	int y() { return ypos; }

	//vlastnosti objektu
	void setSpeed(int sp);
	void movement();

	//flip - prevraceni spritu
	void setFlip(SDL_RendererFlip flip) { this->flip = flip; }
	SDL_RendererFlip getFlip() { return flip; }

	//uprava spritu
	void setsrcScalew(float w) { destRect.w = srcRect.w * w; }

	//kolize
	void setBoudingBox(int w, int h, int offsetx, int offsety); //nastaveni bounding boxu
	//navratove funknce pro jednotlive steny kolizniho boxu
	int getCollisionX() { return boundingposBox.x; }
	int getCollisionX2() { return boundingBox.w + boundingposBox.x; }
	int getCollisionY() { return boundingposBox.y; }
	int getCollisionY2() { return boundingBox.h + boundingposBox.y; }
	
	bool isColliding(GameObject * go); //kontroluje jestli se dotyka zadaneho objektu
	bool isCollidingTop(GameObject * go);
	bool isCollidingBottom(GameObject * go);
	bool isCollidingLeft(GameObject * go);
	bool isCollidingRight(GameObject * go);

	//animace
	void playAnimation(int frames, int speed, bool loop); //prehrat animaci
	void setPlay(bool play) { this->play = play; } //spustit / vypnout animaci
	bool getPlay() { return play; } //vratit jestli animace hraje
	int getmaxFrames() { return maxFrames; } //maximalni pocet framu v animaci
	void setcurFrame(int num) { curFrame = num; } //nastavit cislo framu
	void setplayingFrame(int num) { srcRect.x = framew * num; } // nastavit frame animace - pozice animace
	void setplayingFrameY(int y) { srcRect.y = framew * y; }
	void setplayingFrame(int x, int y) { srcRect.x = framew * x; srcRect.y = framew * y;}
	int getcurFrame() { return curFrame; } //vratit aktualni frame

private:
	int xpos;
	int ypos;

	SDL_Texture * tex;
	SDL_Rect srcRect, destRect;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int speed = 0;

	//bounding box - kolize
	SDL_Texture * boundboxTex;
	SDL_Rect boundingBox, boundingposBox;

	//animace
	float frameTime = 0;
	int maxFrames = 0;
	int curFrame = 0;
	int framew;
	int frameh;
	bool play = true;
};
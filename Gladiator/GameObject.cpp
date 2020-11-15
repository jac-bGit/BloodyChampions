#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "SDL.h"

GameObject::GameObject(){}

//pridat texturu (sprite) pri vytvoreni s defaultni velikosti
GameObject::GameObject(const char * filename, int x, int y, float scale) {
	tex = TextureManager::LoadTexture(filename);

	//konec vykresleni obrazku
	srcRect.w = srcRect.h = 256;
	framew = frameh = 256;
	//pocatek vykresleni
	srcRect.x = srcRect.y = 0;
	//scaling
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;

	//pozice objektu
	xpos = x;
	ypos = y;

	//bounding box
	boundboxTex = TextureManager::LoadTexture("Assets/collider.png");
	setBoudingBox(srcRect.w, srcRect.h, srcRect.x, srcRect.y);
}

//pridat texturu (sprite) pri vytvoreni s nastavitelnout velikosti
GameObject::GameObject(const char * filename, int x, int y, int w, int h, float scale) {
	tex = TextureManager::LoadTexture(filename);

	//konec vykresleni obrazku
	srcRect.w = w;
	srcRect.h = h;

	framew = w;
	frameh = h;
	//pocatek vykresleni
	srcRect.x = srcRect.y = 0;
	//scaling
	destRect.w = srcRect.w * scale;
	destRect.h = srcRect.h * scale;

	//pozice objektu
	xpos = x;
	ypos = y;


	//bounding box
    boundboxTex = TextureManager::LoadTexture("Assets/collider.png");
	setBoudingBox(srcRect.w, srcRect.h, srcRect.x, srcRect.y);
}


//update
void GameObject::update() {
	//pozice objektu - pivot point u prostred
	destRect.x = xpos;
	destRect.y = ypos;

	boundingposBox.x = xpos + boundingBox.x;
	boundingposBox.y = ypos + boundingBox.y;
}

//vykreslovani
void GameObject::render() {
	//vykresli bounding box objektu
	//SDL_RenderCopy(Game::renderer, boundboxTex, &boundingBox, &boundingposBox);

	//vykresli sprite game objectu
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &destRect, 0, 0, getFlip());
}

//vytvorit kolizni box
void GameObject::setBoudingBox(int w, int h, int offsetx, int offsety) {
	
	boundingBox.w = w;
	boundingBox.h = h;
	boundingBox.x = offsetx;
	boundingBox.y = offsety;

	boundingposBox.w = boundingBox.w;
	boundingposBox.h = boundingBox.h;

}

//vraci jestli se objekt zadaneho objetktu
bool GameObject::isColliding(GameObject * go) {

	if (getCollisionX() < go->getCollisionX2() && getCollisionX2() > go->getCollisionX()) {
		if (getCollisionY() < go->getCollisionY2() && getCollisionY2() > go->getCollisionY()) {
			return true;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

//colize s kontretnimi strany objetku
bool GameObject::isCollidingTop(GameObject * go) {
	if (getCollisionX() < go->getCollisionX2() && getCollisionX2() > go->getCollisionX()) {
		if (getCollisionY2() > go->getCollisionY() && getCollisionY() < go->getCollisionY())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool GameObject::isCollidingBottom(GameObject * go) {
	if (getCollisionX() < go->getCollisionX2() && getCollisionX2() > go->getCollisionX()) {
		if (getCollisionY() < go->getCollisionY2() && getCollisionY2() > go->getCollisionY2())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool GameObject::isCollidingLeft(GameObject * go) {
	if (getCollisionY() < go->getCollisionY2() && getCollisionY2() > go->getCollisionY()) {
		if (getCollisionX2() > go->getCollisionX() && getCollisionX() < go->getCollisionX())
			return true;
		else
			return false;
	}
	else
		return false;
}

bool GameObject::isCollidingRight(GameObject * go) {
	if (getCollisionY() < go->getCollisionY2() && getCollisionY2() > go->getCollisionY()) {
		if (getCollisionX() < go->getCollisionX2() && getCollisionX2() > go->getCollisionX2())
			return true;
		else
			return false;
	}
	else
		return false;
}

//prehrati animace
void GameObject::playAnimation(int frames, int speed, bool loop) {

	maxFrames = frames;
	frameTime++;

	if (play) {
		if (frameTime == speed) {
			frameTime = 0;
			srcRect.x += framew;
			curFrame = srcRect.x/framew;
			//dokonceni animace
			if (srcRect.x == framew * frames) {
				srcRect.x = 0;
				play = loop;
			}
		}
	}
}


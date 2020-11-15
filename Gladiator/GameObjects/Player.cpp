#include "Player.h"
#include <iostream>

using namespace std;

//GameObject * target;
const Uint8 * state = SDL_GetKeyboardState(NULL);

//nastaveni hrace pri vytvoreni
Player::Player(const char * sprite, bool first, int x, int y) {
	body = new GameObject(sprite, x, y, 1);
	body->setBoudingBox(50, 125, 100, 256 / 4);

	weapon = new GameObject("Assets/sword1.png", 0, 0, 1);
	weapon->setBoudingBox(256 - 32, 256 / 4, 13, 256 / 2);

	shield = new GameObject("Assets/shield1.png", 0, 0, 1);

	collider = new GameObject("", 100, 0, 256, 30, 1);
	collider->setBoudingBox(60, 20, 256 / 2 - 60 /2, 10);
	
	//pro kontorlovani pohybu
	movx = body->x();
	movy = body->y();

	//promene hrace
	firstPlayer = first;
}

void Player::onLoad() {
	setMaxHp(100);
	setHp(getMaxHp());
	setMaxStamina(100);
	setStamina(getMaxStamina());
	setDmg(10);
	setSpeed(4);
	weapon->setPlay(false);
	shieldDisabled = 0;

	//nastavit pozici
	if (firstPlayer)
		body->setPos(50, 100);
	else
		body->setPos(500, 100);
}

void Player::update() {

	//pokud hrac stale zije
	if (getHp() > 0) {
		body->update();
		weapon->update();
		shield->update();
		collider->update();

		movement();
		weaponController();
		shieldController();
		staminaRegeneration();
		boundToBody(collider, 0, 180);

		//update zaznamenavani pohybu
		movx = body->x();
		movy = body->y();
	}
}

void Player::render() {
	shield->render();
	body->render();
	weapon->render();
	collider->render();
}

//objekty se budou pohybovat s telem hrace
void Player::boundToBody(GameObject * go, int offx, int offy) {
	//pozice
	if (body->getFlip() == SDL_FLIP_NONE) {
		go->setPos(body->x() + offx, body->y() + offy);
		go->setFlip(SDL_FLIP_NONE);
	}
	else if (body->getFlip() == SDL_FLIP_HORIZONTAL) {
		go->setPos(body->x() - offx, body->y() + offy);
		go->setFlip(SDL_FLIP_HORIZONTAL);
	}
}

//pohyb
void Player::movement() {
	
	int winx = 800;
	int winy = 500;
	int offTop = 150;

	//ovladani 8 smeru
	if (firstPlayer) {
		if (state[SDL_SCANCODE_D])
			if (!collider->isCollidingLeft(target->collider) && collider->getCollisionX2() < winx)
			body->setX(body->x() + getspeed());
		if (state[SDL_SCANCODE_A])
			if (!collider->isCollidingRight(target->collider) && collider->getCollisionX() > 0)
			body->setX(body->x() - getspeed());
		if (state[SDL_SCANCODE_S])
			if (!collider->isCollidingTop(target->collider) && collider->getCollisionY2() < winy)
			body->setY(body->y() + getspeed());
		if (state[SDL_SCANCODE_W])
			if (!collider->isCollidingBottom(target->collider) && collider->getCollisionY() > offTop)
			body->setY(body->y() - getspeed());
	}
	else{
		if (state[SDL_SCANCODE_RIGHT])
			if (!collider->isCollidingLeft(target->collider) && collider->getCollisionX2() < winx)
			body->setX(body->x() + getspeed());
		if (state[SDL_SCANCODE_LEFT])
			if (!collider->isCollidingRight(target->collider) && collider->getCollisionX() > 0)
			body->setX(body->x() - getspeed());
		if (state[SDL_SCANCODE_DOWN])
			if (!collider->isCollidingTop(target->collider) && collider->getCollisionY2() < winy)
			body->setY(body->y() + getspeed());
		if (state[SDL_SCANCODE_UP])
			if (!collider->isCollidingBottom(target->collider) && collider->getCollisionY() > offTop)
			body->setY(body->y() - getspeed());
	}

	//flip
	if (body->x() < target->body->x())
		body->setFlip(SDL_FLIP_NONE);
	if (body->x() > target->body->x())
		body->setFlip(SDL_FLIP_HORIZONTAL);
}

//vrati jestli se hrac pohybuje
bool Player::isMoving() {

	if (movx != body->x() || movy != body->y())
		return true;
	else {
		return false;
	}
}

//funkce zajistujici chovani zbrane
void Player::weaponController() {
	
	boundToBody(weapon, -14, -30);

	//utok
	if(!isDefending() && getStamina() > 15)
	attack();

}

//utok
void Player::attack() {

	int staminaCost = 15;

	//rozdeleni klaves
	if (firstPlayer && state[SDL_SCANCODE_F])
		attacking = true;
	if (!firstPlayer && state[SDL_SCANCODE_L])
		attacking = true;

	//utok
	if (attacking) {
		if (!weapon->getPlay())
			weapon->setPlay(true);

		weapon->playAnimation(8, 3, true);
		//dokonceni utoku
		if (weapon->getcurFrame() == weapon->getmaxFrames()) {
			weapon->setPlay(false);
			attacking = false;
			weapon->setcurFrame(0);
			setStamina(getStamina() - staminaCost);

			if (weapon->isColliding(target->body)) {
				if(!target->isDefending())
				target->setHp(target->getHp() - getDmg()); //odebrat hp oponenta
				else {
					target->setStamina(target->getStamina() - 5);
					//ubrat hp openta pokud ma nizkou staminu
					if (target->getStamina() < (target->getMaxStamina() / 2) && target->getStamina() > (target->getMaxStamina() / 4)) {
						target->setHp(target->getHp() - (getDmg() / 4));
					}
					else if (target->getStamina() < (target->getMaxStamina() / 4))
					{
						target->setHp(target->getHp() - (getDmg() / 2));
					}
				}
			}
		}
	}
}

//funkce pro stit
void Player::shieldController() {

	boundToBody(shield, 0, 0);


	//obrana stitem		
	if (!weapon->getPlay() && shieldDisabled == 0) {
		if (firstPlayer) {
			if (state[SDL_SCANCODE_G])
				defending = true;
			else
				defending = false;
		}
		else {
			if (state[SDL_SCANCODE_K])
				defending = true;
			else
				defending = false;
		}
	}
	//nasteveni pozice stitu
	if (defending)
		shield->setplayingFrame(1, 0);
	else
		shield->setplayingFrame(0, 0);

	//shield breaking
	if(getStamina() > 25)
		shieldBreak();

	//nemoznost se branit
	if (shieldDisabled > 0) {
		shieldDisabled--;
	}
}

//prolomeni obrany openenta
void Player::shieldBreak() {

	//spusti shield break
	if (Game::myEvent.type == SDL_KEYDOWN) {
		if (defending) {
			if (firstPlayer) {
				if (state[SDL_SCANCODE_F])
					shieldBreaking = true;
			}
			else {
				if (state[SDL_SCANCODE_L])
					shieldBreaking = true;
			}
		}
	}

	//provedeni shield break
	if (shieldBreaking) {
		if (!shield->getPlay())
			shield->setPlay(true);

		shield->setplayingFrameY(1);
		shield->playAnimation(2, 180, false);

		setStamina(getStamina() - 25);
		shieldBreaking = false;

		if (weapon->isColliding(target->body)) {
			if (target->isDefending()) {
				target->setShieldDisabled(3 * 60);
				target->setStamina(target->getStamina() - 10);
				target->setDefending(false);
			}
			else
			{
				target->setHp(target->getHp() -5);
			}
		}
	}

}


//regenerace staminy
void Player::staminaRegeneration() {

	stamDelay++;

	if (stamDelay == 8) {
		if (getStamina() < getMaxStamina() && !defending) {
			if(isMoving())
				setStamina(getStamina() + 1);
			else
				setStamina(getStamina() + 2);
		}
		stamDelay = 0;
	}

	//pokud se dostane stamina pod nulu
	if (getStamina() < 0) 
		setStamina(0);

}
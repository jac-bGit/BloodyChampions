#include <iostream>
#include <stdlib.h>
#include <time.h>   

#include "Enemy.h"

//cil pro nasledovani
//Player * target;

//
int xrange = 75;
int yrange = 10;

//hranice areny
int winx = 800;
int winy = 500;
int offTop = 175;
int offBottom = 30;
int offSide = 50;

//nastaveni pri vytvoreni
Enemy::Enemy(const char * bodySpr, const char * wepSpr, const char * shieldSpr, Player * targ) {
	body = new GameObject(bodySpr, 0, 250, 1);
	body->setBoudingBox(50, 125, 100, 256 / 4);
	weapon = new GameObject(wepSpr, 0, 0, 1);
	weapon->setBoudingBox(256 - 32, 256 / 4, 13, 256 / 2);

	shield = new GameObject(shieldSpr, 0, 0, 1);

	collider = new GameObject("", 100, 0, 256, 20, 1);
	collider->setBoudingBox(60, 20, 256 / 2 - 60 / 2, 10);

	target = targ;

	//pro kontorlovani pohybu
	movx = body->x();
	movy = body->y();
}


void Enemy::onLoad() {

	setHp(getMaxHp());
	setStamina(getMaxStamina());
	blockSucces = randInt(0, 10);
	weapon->setPlay(false);
	shieldBreakWait = shieldBreakDelay;

	body->setPos(500, 100);

	//save stamina
	saveStamina = int(getMaxStamina() * saveStamPerc);
	fightStamina = int(getMaxStamina() * fightStamPerc);
	//std::cout << "save stamina " << saveStamina << std::endl;

}

//nastaveni vlastnosti bojovnika
//zakladni
void Enemy::setAbilities(int maxHp, int speed) {
	setMaxHp(maxHp);
	setSpeed(speed);
}
//bojove vlastnosti
void Enemy::setFightingAbs(int dmg, int minAttackDelay, int maxAttackDelay) {
	setDmg(dmg);
	this->minAttackDelay = minAttackDelay;
	this->maxAttackDelay = maxAttackDelay;
}
//vlastnosti pro praci se stitem
void Enemy::setBlockingAbs(int blockChance, int maxBlockWait, int minBlockWait, int shieldBreakDelay) {
	this->blockChance = blockChance;
	this->maxBlockWait = maxBlockWait;
	this->minBlockWait = minBlockWait;
	this->shieldBreakDelay = shieldBreakDelay;
}
//vlastnosti pro praci se staminou
void Enemy::setStaminaAbs(int maxStamina, float saveStamPerc, float fightStamPerc) {
	setMaxStamina(maxStamina);
	this->saveStamPerc = saveStamPerc;
	this->fightStamPerc = fightStamPerc;
}

void Enemy::update(){

	//randomizace
	srand(time(NULL));

	//pokud nepritel stale zije
	if (getHp() > 0) {
		shield->update();
		body->update();
		weapon->update();
		collider->update();

		boundToBody(collider, 0, 180);


		movement();

		weaponController();
		shieldController();
		staminaRegeneration();

		//pro kontorlovani pohybu
		movx = body->x();
		movy = body->y();
	}
}

void Enemy::render() {
	shield->render();
	body->render();
	weapon->render();
	collider->render();
}

//objekty se budou pohybovat s telem nepritele
void Enemy::boundToBody(GameObject * go, int offx, int offy) {
	//pozice objektu
	if (body->getFlip() == SDL_FLIP_NONE) {
		go->setPos(body->x() + offx, body->y() + offy);
		go->setFlip(SDL_FLIP_NONE);
	}
	else if (body->getFlip() == SDL_FLIP_HORIZONTAL) {
		go->setPos(body->x() - offx, body->y() + offy);
		go->setFlip(SDL_FLIP_HORIZONTAL);
	}
}

//pohyb nepritele
void Enemy::movement() {

	
	if (!fallback) {

		goThrough = false;

		//nasledovat cil - x pos
		if (body->x() < target->body->x() - xrange)
			body->setX(body->x() + getspeed());
		if (body->x() > target->body->x() + xrange)
			body->setX(body->x() - getspeed());
		//y pos
		if (body->y() < target->body->y() - yrange)
			body->setY(body->y() + getspeed());
		if (body->y() > target->body->y() + yrange)
			body->setY(body->y() - getspeed());
	}
	else //pokud ustup
	{
		doFallback();
	}

	if (getStamina() < saveStamina)
		fallback = true;

	if (fallback && getStamina() > fightStamina) {
		fallback = false;
	}

	//konec prace se staminou a pohybem

	//flip
	if (body->x() < target->body->x())
		body->setFlip(SDL_FLIP_NONE);
	else
		body->setFlip(SDL_FLIP_HORIZONTAL);
}

//pohybuje se 
bool Enemy::isMoving() {

	if (movx != body->x() || movy != body->y())
		return true;
	else {
		return false;
	}
}

//ustup 
void Enemy::doFallback() {
	//ustup
	if (fallback) {
		//doleva
		if (body->x() < target->body->x()) {
			if (collider->getCollisionX() > offSide) {
				if (!goThrough)
					body->setX(body->x() - getspeed());
			}
			else {
				//std::cout << "jsem v levo" << std::endl;
				toRightside = false; //je v levo

				if (target->body->x() < winx / 4)  //pokud se hrac nachazi v leve tretine areny
					goThrough = true;
			}
		}
		//obchazeni hrace z leva
		if (!toRightside && goThrough) {
			if (target->body->x() < winx / 2) { //pokud se hrac nachazi v leve pulce areny
				
				if (body->x() < target->body->x() + 100) { //dokud neprejde kolem hrace
					body->setX(body->x() + getspeed());
				}
				else { //po te co prejde kolem hrace na druhou stranu
					goThrough = false;
				}
			}
			else {
				goThrough = false;
			}
		}


		//doprava
		if (body->x() > target->body->x()) {
			if (collider->getCollisionX2() < (winx - offSide)) {
				if (!goThrough)
					body->setX(body->x() + getspeed());
			}
			else {
				//std::cout << "jsem v pravo" << std::endl;
				toRightside = true;
				//if (target->body->x() > winx)  //pokud se hrac nachazi v prave tretine areny
					goThrough = true;
			}
		}
		//obchazeni hrace z prava
		if (toRightside && goThrough) {
			if (target->body->x() > winx / 2) { //pokud se hrac nachazi v prave pulce areny

				if (body->x() > target->body->x() - 100) { //dokud neprejde kolem hrace
					body->setX(body->x() - getspeed());
				}
				else { //po te co prejde kolem hrace na druhou stranu
					goThrough = false;
				}
			}
			else {
				goThrough = false;
			}
		}

		//uhybani dolu a nahoru
		if (goThrough) {
			if (body->y() > target->body->y() - yrange) {
				if (collider->getCollisionY2() < winy - offBottom)
					body->setY(body->y() + getspeed());
			}
			else {
				if (collider->getCollisionY() > offTop) {
					body->setY(body->y() - getspeed());
				}
			}
		}

		//konec obchazeni kolem hrace

	}
}



//zbran a utok
void Enemy::weaponController() {

	boundToBody(weapon, -14, -30);

	//pokud je v blizkosti cile a ma dostatek staminy...
	if (weapon->isColliding(target->body) && stamina > 15 && !defending) {
		if (attackDelay == 0) {
			attacking = true;
			attackDelay = randInt(minAttackDelay, maxAttackDelay);
			blockSucces = randInt(0, 10);
			//std::cout << "att delay: " << attackDelay << std::endl;
			//std::cout << "block succes: " << blockSucces << std::endl;
		}
	}

	//prodleva mezi utoky
	if (attackDelay > 0)
		attackDelay--;

		attack();
}

//provedeni utoku
void Enemy::attack() {
	
	if (attacking) {
		if (weapon->getPlay() == false)
			weapon->setPlay(true);

		weapon->playAnimation(8, 3, true);
		//dokonceni utoku
		if (weapon->getcurFrame() == weapon->getmaxFrames()) {
			weapon->setPlay(false);
			attacking = false;
			weapon->setcurFrame(0);
			setStamina(getStamina() - 15);
			//pokud se zbran dotkne cile
			if (weapon->isColliding(target->body)) {
				if (!target->isDefending()) {
					target->setHp(target->getHp() - getDmg());
				}
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

//funkce pro stit-----------------------------------------------------
void Enemy::shieldController(){
	boundToBody(shield, 0, 0);

	//kryti
	if (body->isColliding(target->weapon) && target->weapon->getPlay() &&
		!weapon->getPlay() && !shieldDisabled) {
		//pokud se podari kryti (random cislo je v mensi nez hodnota sance)
		if (blockChance > blockSucces && !defending) {
			blockWait = randInt(minBlockWait, maxBlockWait);
		}
		//std::cout << "shield waiting: " << blockWait << std::endl;
	}


	if (blockWait > 0) {
		defending = true;
		blockWait--;
	}
	else {
		defending = false;
	}


	//animace stitu
	if (defending)
		shield->setplayingFrame(1, 0);
	else
		shield->setplayingFrame(0, 0);


	//pokud se nemuze branit
	if (shieldDisabled > 0) {
		blockWait = 0;
		shieldDisabled--;
	}


	//shield break
	shieldBreak();
}

//prolomeni obrany oponenta
void Enemy::shieldBreak() {

	if (weapon->isColliding(target->body) && stamina > 25 && target->isDefending()) {
		if (shieldBreakWait <= 0) {
			shieldBreaking = true;
		}
		else {
			shieldBreakWait--;
		}
	}

	//obnoveni cekani
	if (!weapon->isColliding(target->body)) {
		shieldBreakWait = shieldBreakDelay;
	}

	//provedeni shield break
	if (shieldBreaking) {
		if (!shield->getPlay())
			shield->setPlay(true);

		shield->setplayingFrameY(1);
		shield->playAnimation(2, 180, false);

		setStamina(getStamina() - 25);
		shieldBreaking = false;
		shieldBreakWait = shieldBreakDelay;

		if (weapon->isColliding(target->body)) {
			if (target->isDefending()) {
				target->setShieldDisabled(3 * 60);
				target->setStamina(target->getStamina() - 10);
				target->setDefending(false);
			}
			else
			{
				target->setHp(target->getHp() - 5);
			}
		}
	}
}

//regenerace staminy
void Enemy::staminaRegeneration() {
	stamDelay++;

	if (stamDelay == 8) {
		if (getStamina() < getMaxStamina() && !defending) {
			if (isMoving())
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

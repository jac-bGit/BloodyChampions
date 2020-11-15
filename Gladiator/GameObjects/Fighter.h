#pragma once
#include "../GameObject.h"

class Fighter
{

protected:
	int startx;
	int starty;

	//pohyb
	int movx;
	int movy;

	int maxHp;
	int hp;
	int maxStamina;
	int stamina;

	int speed;
	int dmg;

	bool defending = false;
	//nemoznost se branit
	int shieldDisabled = 0;

	int stamDelay = 0; //prodleni regenerace staminy

public:
	//zakladni
	virtual void onLoad() {}
	virtual void update() {}
	virtual void render() {}

	//zivoty
	void setMaxHp(int maxHp) { this->maxHp = maxHp; }
	int getMaxHp() { return maxHp; }

	void setHp(int hp) { this->hp = hp; }
	int getHp() { return hp; }

	//stamina
	void setMaxStamina(int maxStam) { this->maxStamina = maxStam; }
	int getMaxStamina() { return maxStamina; }

	void setStamina(int stamina) { this->stamina = stamina; }
	int getStamina() { return stamina; }

	//rychlost
	void setSpeed(int speed) { this->speed = speed; }
	int getspeed() { return speed; }

	//poskozeni
	void setDmg(int dmg) { this->dmg = dmg; }
	int getDmg() { return dmg; }

	//obrana
	void setDefending(bool defend) { defending = defend; }
	void setShieldDisabled(int delay) { shieldDisabled = delay; }


	//casti tela
	GameObject * body;
	GameObject * weapon;
	GameObject * shield;
	GameObject * collider;

	//fuknce bojovnika
	//virtual void shieldController();
	bool isDefending() { return defending; }
	virtual void boundToBody(GameObject * go, int offx, int offy) {};
	virtual void movement() {}
	virtual void weaponController() {}
	virtual void attack() {}
	virtual void shieldController() {}
	virtual void shieldBreak() {}
	virtual void staminaRegeneration() {}

	bool isMoving();

	//oponent
	Fighter * target;
	//funknce urci cil (oponenta), ktery muze byt objekt ze tridy Player nebo Enemy
	void setTarget(Fighter * targ) { target = targ; }
};
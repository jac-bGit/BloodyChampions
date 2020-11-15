#pragma once
#include "../GameObject.h"
#include "../Game.h"
#include "Fighter.h"

class Player;
class GameObject;

class Enemy : public Fighter
{
public:
	Enemy(const char * bodySpr, const char * wepSpr, const char * shieldSpr, Player * targ);

	void onLoad();
	void update();
	void render();

	//vlastnosti
	void boundToBody(GameObject * go, int offx, int offy);

	void movement();
	bool isMoving();
	void doFallback(); //obchazeni

	//nastaveni
	void setAbilities(int maxHp, int speed);
	void setFightingAbs(int dmg, int minAttackDelay, int maxAttackDelay);
	void setBlockingAbs(int blockChance, int minBlockWait, int maxBlockWait, int shieldBreakDelay);
	void setStaminaAbs(int maxStamina, float saveStamPerc, float fightStamPerc);

	//funkce 
	void weaponController();
	void attack();
	void shieldController();
	void shieldBreak();
	void staminaRegeneration();

	//nahodna int hodnota
	int randInt(int min, int max) {return rand() % (max - min) + min;}

private:

	//ustup
	bool fallback = false; 
	bool fallbackSet = true;
	bool goThrough = false;  //projit pres hrace
	bool toRightside = false; //ustupuje do prava

	//zbran
	bool attacking = false;
	int maxAttackDelay;
	int minAttackDelay;
	int attackDelay = 0; //cas mezi jednotlivymi utoky

	//stit
	int blockChance; //sance na blokaci
	int blockSucces;
	int maxBlockWait;
	int minBlockWait;
	int blockWait; //po vykryti utoku cekat s pripravenym stitem
	
	bool shieldBreaking = false;
	int shieldBreakDelay; //urceny cas pro cekani
	int shieldBreakWait; //aktualni ubyvajici cas

	//prace se staminou
	float saveStamPerc;
	int saveStamina;
	float fightStamPerc;
	int fightStamina;
};

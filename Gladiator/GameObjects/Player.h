#pragma once
#include "../GameObject.h"
#include "../Game.h"
#include "Fighter.h"

class GameObject;

class Player: public Fighter
{
public:
	Player(const char * sprite, bool first, int x, int y);
	~Player();

	//zakladni
	void onLoad();
	void update();
	void render();

	//funkce hrace
	void boundToBody(GameObject * go, int offx, int offy);
	void movement();
	bool isMoving();
	void weaponController();
	void attack();
	void shieldController();
	void shieldBreak();
	void staminaRegeneration();

private:
	//pro rozdeleni hracu - napr. ruzne ovladani 
	bool firstPlayer;
	SDL_Event event;

	//zbran
	bool attacking = false;

	bool shieldBreaking = false;

	//stit
	//bool defending = false;

};


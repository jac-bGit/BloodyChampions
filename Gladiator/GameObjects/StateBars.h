#pragma once
#include "../GameObject.h"
#include "../Game.h"
#include "Fighter.h"
#include "../Text.h"

class Fighter;

class StateBars 
{
public:
	StateBars(int x, int y);

	//zakladni
	void update();
	void render();

	void setFighter(Fighter * fighter) { this->fighter = fighter; }

	float getHpState() { return float(fighter->getHp()) / float(fighter->getMaxHp()); }
	float getStaminaState() { return float(fighter->getStamina()) / float(fighter->getMaxStamina()); }
	//zmenit delku ukazatele na zaklade hodnoty
	void barSize(GameObject * bar, float percentage);

private:
	Fighter * fighter;
	GameObject * hpBar;
	GameObject * staminaBar;
	GameObject * barBg;
	GameObject * barBg2;
	Text * hpTxt;
	Text * staminaTxt;

};
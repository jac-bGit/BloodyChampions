#include "StateBars.h"

#include <iostream>
#include <string>

StateBars::StateBars(int x, int y) {
	barBg = new GameObject("Assets/gui/bg.png", x, y, 100, 20, 1);
	hpBar = new GameObject("Assets/gui/hpbar.png", x, y, 100, 20, 1);

	barBg2 = new GameObject("Assets/gui/bg.png", x, y + 20, 100, 20, 1);
	staminaBar = new GameObject("Assets/gui/staminabar.png", x, y + 20, 100, 20, 1);
}

void StateBars::update() {
	barBg->update();
	barBg2->update();
	hpBar->update();
	staminaBar->update();
	//hpTxt->setText("100");

	//zmenit delku ukazatele na zaklade hodnoty
	hpBar->setsrcScalew(getHpState());
	staminaBar->setsrcScalew(getStaminaState());
	//hpBar->setsrcRectW(15);
}
void StateBars::render() {
	barBg->render();
	barBg2->render();

	hpBar->render();
//	hpTxt->setText(std::to_string(fighter->getHp()));
	//hpTxt->render(hpBar->x(), hpBar->y());

	staminaBar->render();
	//staminaTxt->render(staminaBar->x(), staminaBar->y());
	//staminaTxt->setText(std::to_string(fighter->getStamina()));

}

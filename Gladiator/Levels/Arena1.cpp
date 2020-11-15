/*#include "Arena1.h"

#include <iostream>

//vlozeni objektu do sceny
Arena1::Arena1() {
	player = new Player(1, 0, 0);
	enemy = new Enemy(player);

	player->setTarget(enemy);

	//gui
	statebar = new StateBars(100, 50);
	statebar->setFighter(player);
	statebar2 = new StateBars(600, 50);
	statebar2->setFighter(enemy);
}


void Arena1::update() {
	player->update();
	enemy->update();

	statebar->update();
	statebar2->update();
	std::cout << "works" << std::endl;
}


void Arena1::render() {
	player->render();
	enemy->render();

	statebar->render();
	statebar2->render();
}

void Arena1::handle_events() {

}

Arena1::~Arena1() {
	//delete[] player;
}*/
#pragma once
#include "../Game.h"
#include "../GameObject.h"

class Level
{
public:
	virtual void init() {};
	virtual void handleEvents() {};
	virtual void update() {};
	virtual void render() {};

	void restartLevel();

private:

};


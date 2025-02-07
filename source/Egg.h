#pragma once
#include "Animation.h"


class Egg
{
public:
	Egg();
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }
private:
	sf::Clock eggTimer;
	Animation sprite;
};
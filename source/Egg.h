#pragma once
#include "Animation.h"
#include "Collidable.h"


class Egg : public Collidable
{
public:
	Egg();
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }
private:
	sf::Clock eggTimer;
	Animation sprite;
};
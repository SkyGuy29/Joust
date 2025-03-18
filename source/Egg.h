#pragma once
#include "Animation.h"
#include "Collidable.h"


class Egg : public Collidable
{
public:
	Egg();
	void update() override;
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }

	void drawTo(sf::RenderWindow&);
private:
	sf::Clock eggTimer;
	Animation sprite;
};
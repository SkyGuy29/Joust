#pragma once
#include "Animation.h"
#include "Collidable.h"


class Egg : public Collidable
{
public:
	Egg();
	Egg(sf::Vector2f, sf::Vector2f);
	void update() override;
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }

	void drawTo(sf::RenderWindow&);
private:
	sf::Clock eggTimer;
	Animation sprite;
};
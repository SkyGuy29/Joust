#pragma once
#include "Animation.h"
#include "Collidable.h"


class Egg : public Collidable
{
public:
	Egg();
	Egg(sf::Vector2f, sf::Vector2f, EnemyTypes);
	void update() override;
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }

	EnemyTypes getType()
	{
		return type;
	}

	void drawTo(sf::RenderWindow&);
private:

	EnemyTypes type;
	sf::Clock eggTimer;
	Animation sprite;
};
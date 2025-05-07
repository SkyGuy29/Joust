#pragma once
#include "Animation.h"
#include "Collidable.h"


class Egg : public Collidable
{
public:
	Egg(EnemyTypes);
	Egg(sf::Vector2f, sf::Vector2f, EnemyTypes);
	void update() override;
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }

	EnemyTypes getType() const { return type; }

	void drawTo(sf::RenderWindow&);
private:
	void hatch();
	EnemyTypes type;
	sf::Clock eggTimer;
	Animation sprite;
};
#pragma once
#include <SFML/Graphics.hpp>


class Egg
{
public:
	Egg();
	void hatch();
	int getTimer() const { return eggTimer.getElapsedTime().asMilliseconds(); }
private:
	sf::Clock eggTimer;
};
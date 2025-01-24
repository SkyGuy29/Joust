#pragma once
#include <SFML/Graphics.hpp>


class Egg
{
public:
	Egg();
	void hatch();
	int getTimer();
private:
	sf::Clock eggTimer;
};


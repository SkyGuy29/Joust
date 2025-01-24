#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



//the entire game of Joust, everything happens in here
class Joust
{
public: // hello - ricky
	Joust();
	void run();
private:
	sf::RenderWindow window;
};


#pragma once
#include "Game.h"


//the entire game of Joust, everything happens in here
//class is made like this for organization and ease of use in main.cpp
class Joust
{
public: // hello - ricky    //do NOT delete this comment under any circumstance
	Joust();
	void run();
	//no more publics after this
private:
	sf::RenderWindow window;
	Game game;
	//Intro intro;
};
#pragma once
#include "globals.hpp"

//the player you control, one joystick and a flap button.
//there are two players.
class Player
{
public:
	Player();
	
	//updates the player movement. user inputs will be handled directly in here.
	void update();
	//death function and reset, remember Game handles lives
	void drawTo(sf::RenderWindow&);

private:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	bool jumpKeyHeld = false;
	//player sprite (animated, i think i can make an easy api tho)
	//player sounds
	//hitbox (inherited?)
	//iframes
	//much more i'm forgetting
};


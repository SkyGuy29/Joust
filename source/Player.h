#pragma once
#include "globals.hpp"
#include "Animation.h"

//the player you control, one joystick and a flap button.
//there are two players.
class Player
{
public:
	Player();
	
	//updates the player movement. user inputs will be handled directly in here.
	void update();

	sf::RectangleShape getHitbox();

	sf::Vector2f getVelocity();

	//death function and reset, remember Game handles lives


	void drawTo(sf::RenderWindow&);

private:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	bool jumpKeyHeld = false;
	//player sprite (animated, i think i can make an easy api tho)
	//Animation sprite;
	//player sounds
	//hitbox (inherited?)
	//iframes
	//much more i'm forgetting
};


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

	sf::FloatRect getHitbox() const { return hitbox.getGlobalBounds(); }

	sf::Vector2f getVelocity() const { return vel; }

	//death function and reset, remember Game handles lives


	void drawTo(sf::RenderWindow&);

private:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	Animation sprite;

	bool jumpKeyHeld = false;
	int flapSprite = 0;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};
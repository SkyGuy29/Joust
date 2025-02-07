#pragma once
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

	//puts the player on top of a platform and lets it run and stuff
	void setOnGround(float);

	//
	void setOffGround() { onGround = false; sprite.setAnimation(AnimationNames::P1_FLY); }

	//death function and reset, remember Game handles lives


	void drawTo(sf::RenderWindow&);

private:
	//i hate sfml keyboard detection naming so i made a mediocre fix
	bool isLeftPressed();
	bool isRightPressed();
	bool isDownPressed();
	bool isJumpPressed();

	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	Animation sprite;

	bool jumpKeyHeld = false, onGround = false; //should be true to start but for now leave false
	int flapSprite = 0;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};
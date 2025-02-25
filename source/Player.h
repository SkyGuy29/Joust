#pragma once
#include "Animation.h"
#include "Platform.h"

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

	//puts the player on top of a platform and lets it run on it.
	//the parameter is the top of the platform.
	void setOnGround(float);

	//lets player know that it is no longer on the ground.
	void setOffGround() { onGround = false; sprite.setAnimation(AnimationNames::P1_FLY); }

	//death function and reset, remember Game handles lives
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void bounceSetLeft(Platform);
	void bounceSetRight(Platform);

	void bounceX();
	void bounceY();

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
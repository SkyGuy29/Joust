#pragma once
#include "Animation.h"
#include "Collidable.h"

//the player you control, one joystick and a flap button.
//there are two players.
class Player : public Collidable
{
public:
	Player();
	
	//updates the player movement. user inputs will be handled directly in here.
	void update() override;

	//puts the player on top of a platform and lets it run on it.
	//the parameter is the top of the platform.
	void setOnGround(float, int) override;

	//lets player know that it is no longer on the ground.
	void setOffGround() override
	{ Collidable::setOffGround(); sprite.setAnimation(AnimationNames::P1_FLY); }

	//death function and reset, remember Game handles lives
	void setPosition(sf::Vector2f) override;
	void bounceSetLeft(Platform) override;
	void bounceSetRight(Platform) override;

	void drawTo(sf::RenderWindow&);

private:
	//i hate sfml keyboard detection naming so i made a mediocre fix
	bool isLeftPressed();
	bool isRightPressed();
	bool isDownPressed();
	bool isJumpPressed();

	Animation sprite;

	bool jumpKeyHeld = false, skid = false;
	int leftTimer = 0, rightTimer = 0, speed = 0, frameCounter = 0;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};
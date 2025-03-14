#pragma once
#include "Collidable.h"
#include "Animation.h"

class Enemy : public Collidable
{
public:
	Enemy();

	//updates the player movement. user inputs will be handled directly in here.
	void update() override;

	//puts the player on top of a platform and lets it run on it.
	//the parameter is the top of the platform.
	void setOnGround(float, int) override;

	//lets player know that it is no longer on the ground.
	void setOffGround() override
	{
		//out of bounds error if called
		Collidable::setOffGround(); sprite.setAnimation(AnimationNames::BOUNDER_FLY);
		//this does get called right now so um yeah that's fun
	}

	//death function and reset, remember Game handles lives
	void setPosition(sf::Vector2f) override;
	void bounceSetLeft(Platform) override;
	void bounceSetRight(Platform) override;

	void drawTo(sf::RenderWindow&);

private:

	Animation sprite;

	bool skid = false;
	int leftTimer = 0, rightTimer = 0, speed = 0, frameCounter = 0;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};


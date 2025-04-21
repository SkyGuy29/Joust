#pragma once
#include "Collidable.h"
#include "Animation.h"
#include "Player.h"

class Enemy : public Collidable
{
public:
	//Enemy();

	//updates the player movement. user inputs will be handled directly in here.
	virtual void update(Player[2]);

	//puts the player on top of a platform and lets it run on it.
	//the parameter is the top of the platform.
	virtual void setOnGround(float, int) override;

	//lets player know that it is no longer on the ground.
	virtual void setOffGround() override
	{
		//out of bounds error if called
		Collidable::setOffGround(); sprite.setAnimation(AnimationNames::BOUNDER_FLY);
		//this does get called right now so um yeah that's fun
	}

	//death function and reset, remember Game handles lives
	virtual void setPosition(sf::Vector2f) override;
	virtual void bounceSetLeft(Platform&) override;
	virtual void bounceSetRight(Platform&) override;

	virtual void drawTo(sf::RenderWindow&);


protected:

	Animation sprite;

	bool skid = false;
	int leftTimer = 0, rightTimer = 0, speed = 0, frameCounter = 0, flapCounter = 0, target = -1;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};


#pragma once
#include "Collidable.h"
#include "Animation.h"
#include "Player.h"

class Enemy : public Collidable
{
public:
	//Enemy();

	//updates the player movement. user inputs will be handled directly in here.
	virtual void update(Player[2], int activePlatforms[PlatformNames::PLATFORM_COUNT]);

	//puts the player on top of a platform and lets it run on it.
	//the parameter is the top of the platform.
	virtual void setOnGround(float, int) override;

	//lets player know that it is no longer on the ground.
	virtual void setOffGround() override
	{ Collidable::setOffGround(); sprite.setAnimation(AnimationNames::BOUNDER_FLY); }

	//death function and reset, remember Game handles lives
	virtual void setPosition(sf::Vector2f) override;
	virtual void bounceSetLeft(Platform&) override;
	virtual void bounceSetRight(Platform&) override;

	virtual void drawTo(sf::RenderWindow&);

	virtual EnemyTypes getType()
	{
		return type;
	}

	void setRespawn(int);


	virtual EnemyTypes getType() { return type; }
protected:
	Animation sprite;

	EnemyTypes type;

	bool skid = false, spawn = true;
	int leftTimer = 0, rightTimer = 0, speed = 0, frameCounter = 0, flapCounter = 0, target = -1;
	//player sounds
	//iframes timer
	//much more i'm forgetting
};


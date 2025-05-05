#pragma once
#include "../Enemy.h"

class Hunter : public Enemy
{
public:
	Hunter();
	Hunter(sf::Vector2f);

	//updates the player movement. user inputs will be handled directly in here.
	void update(Player[2], int activePlatforms[PlatformNames::PLATFORM_COUNT]) override;

	void setOffGround() override
	{
		//out of bounds error if called
		Collidable::setOffGround(); sprite.setAnimation(AnimationNames::HUNTER_FLY);
		//this does get called right now so um yeah that's fun
	}

	void setOnGround(float, int) override;

private:

};

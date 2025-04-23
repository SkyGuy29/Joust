#pragma once
#include "../Enemy.h"

class Bounder : public Enemy
{
public:
	Bounder();
	Bounder(sf::Vector2f);

	//updates the player movement. user inputs will be handled directly in here.
	void update(Player[2]) override;

	void setOffGround() override
	{
		//out of bounds error if called
		Collidable::setOffGround(); sprite.setAnimation(AnimationNames::BOUNDER_FLY);
		//this does get called right now so um yeah that's fun
	}

	void setOnGround(float, int) override;

private:
};

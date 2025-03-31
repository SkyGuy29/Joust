#include "Bounder.h"


Bounder::Bounder()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(500, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::BOUNDER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	vel.x = SPEED_INC_X;
}


void Bounder::update()
{
	//5 on the counter for staying on the same plane
	if (hitbox.getPosition().y > WINDOW_Y * WINDOW_SCALE * 3 / 4 && flapCounter >= 5)
	{
		vel.y -= 2 * (WINDOW_SCALE / 3.f);

		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down
			/*
					if (isLeftPressed())
					{
						sprite.setFaceRight(false);
						if (vel.x > -SPEED_MAX_X)
							vel.x -= SPEED_INC_X;
					}
					else if (isRightPressed())
					{
						sprite.setFaceRight(true);
						if (vel.x < SPEED_MAX_X)
							vel.x += SPEED_INC_X;
					}
					*/
		}
		else
			setOffGround();
		flapCounter = 0;
	}


	flapCounter++;
	Enemy::update();
}


void Bounder::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::BOUNDER_GROUND);
	Enemy::setOnGround(newYValue, platform);
}

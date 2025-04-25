#include "Shadow.h"


Shadow::Shadow()
{
	type = SHADOW;
	hitbox.setPosition((rand() % 5 + 1) * 100, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::SHADOW_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X * 3;
}


Shadow::Shadow(sf::Vector2f pos)
{
	type = SHADOW;
	hitbox.setPosition(pos);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::SHADOW_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X * 3;
}


void Shadow::update(Player player[2])
{
	float closerPlayerF = 0;
	int closerPlayer = 0;

	closerPlayerF = distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().x),
		sf::Vector2f(player[0].getPosition().x, player[0].getPosition().x));

	if (closerPlayerF > distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().x),
		sf::Vector2f(player[1].getPosition().x, player[1].getPosition().x)))
	{
		closerPlayerF = distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().x),
			sf::Vector2f(player[1].getPosition().x, player[1].getPosition().x));
		closerPlayer = 1;
	}

	target = closerPlayer;

	if (currentPlatform == -1 && flapCounter >= 5)
		sprite.setFrame(0); //flapping, wings up
	//5 on the counter for staying on the same plane
	if (hitbox.getPosition().y > WINDOW_Y * WINDOW_SCALE * 3 / 4 && flapCounter >= 10)
	{
		vel.y -= 2 * (WINDOW_SCALE / 3.f);

		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down
		}
		else
			setOffGround();
		flapCounter = 0;
	}
	else if (hitbox.getPosition().y > player[closerPlayer].getPosition().y && flapCounter >= 13)
	{
		vel.y -= 3 * (WINDOW_SCALE / 3.f);
		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down
		}
		else
			setOffGround();
		flapCounter = 0;
	}
	flapCounter++;
	Enemy::update(player);

}


void Shadow::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::SHADOW_GROUND);
	Enemy::setOnGround(newYValue, platform);
}
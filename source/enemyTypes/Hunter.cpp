#include "Hunter.h"


Hunter::Hunter()
{
	type = HUNTER;
	hitbox.setPosition((rand() % 5 + 1) * 100, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::HUNTER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X * 2;
}


Hunter::Hunter(sf::Vector2f pos)
{
	type = HUNTER;
	hitbox.setPosition(pos);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::HUNTER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X * 2;
}


void Hunter::update(Player player[2], int activePlatforms[PlatformNames::PLATFORM_COUNT])
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

	if (player[0].getRespawning() == true && target == 0)
		target = -1;

	if (currentPlatform == -1 && flapCounter >= 5)
		sprite.setFrame(0); //flapping, wings up
	//5 on the counter for staying on the same plane
	if (target == -1)
	{
		if (flapCounter >= 10 && currentPlatform == -1)
		{
			sprite.setFrame(1);
			flapCounter = 0;
			vel.y = -1.5;
		}
		else if (flapCounter >= 5)
			vel.y = 1.5;

	}
	else if (hitbox.getPosition().y > WINDOW_Y * WINDOW_SCALE * 3 / 4 && flapCounter >= 10)
	{
		vel.y -= 2 * (WINDOW_SCALE / 3.f);

		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down


		}
		else
		{
			activePlatforms[currentPlatform]--;
			setOffGround();
		}
		flapCounter = 0;
	}
	else if (hitbox.getPosition().y > player[target].getPosition().y && flapCounter >= 11)
	{
		vel.y -= 1.5 * (WINDOW_SCALE / 3.f);
		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down
		}
		else
		{
			activePlatforms[currentPlatform]--;
			setOffGround();
		}
		flapCounter = 0;
	}
	flapCounter++;

	Enemy::update(player, activePlatforms);
}


void Hunter::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::HUNTER_GROUND);
	Enemy::setOnGround(newYValue, platform);
}

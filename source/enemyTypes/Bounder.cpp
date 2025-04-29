#include "Bounder.h"


Bounder::Bounder()
{
	type = BOUNDER;
	hitbox.setPosition((rand() % 5 + 1) * 100, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::BOUNDER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X;
}


Bounder::Bounder(sf::Vector2f pos)
{
	type = BOUNDER;
	hitbox.setPosition(pos);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::BOUNDER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	vel.x = SPEED_INC_X;
}


void Bounder::update(Player player[2])
{
	float closerPlayerF = 0;
	int closerPlayer = 0;

	closerPlayerF = distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y),
		sf::Vector2f(player[0].getPosition().x, player[0].getPosition().y));

	if (closerPlayerF > distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y),
		sf::Vector2f(player[1].getPosition().x, player[1].getPosition().y)))
	{
		closerPlayerF = distBetween(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y),
			sf::Vector2f(player[1].getPosition().x, player[1].getPosition().y));
		closerPlayer = 1;
	}
	
	//std::cout << closerPlayerF << std::endl;

	if (currentPlatform == -1 && flapCounter >= 5)
		sprite.setFrame(0); //flapping, wings up
	//5 on the counter for staying on the same plane

	if (closerPlayerF < 500 && target == -1)
	{
		target = closerPlayer;
		vel.y = -2;
		flapCounter = 11;
	}

	if (player[0].getRespawning() == true && target == 0)
		target = -1;


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
	else if (hitbox.getPosition().y > player[target].getPosition().y && flapCounter >= 11)
	{
		vel.y -= 1.5 * (WINDOW_SCALE / 3.f);
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


void Bounder::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::BOUNDER_GROUND);
	Enemy::setOnGround(newYValue, platform);
}

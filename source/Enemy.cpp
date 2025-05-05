#include "Enemy.h"


/*Enemy::Enemy()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(500, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::SHADOW_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	vel.x = SPEED_INC_X;
}*/


void Enemy::update(Player player[2], int activePlatforms[PlatformNames::PLATFORM_COUNT])
{
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE));
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.move(vel);

	//same as in player.cpp, screen boundary collision
	//vertical
	if (hitbox.getPosition().y - hitbox.getSize().y / 2.f < 0)
	{
		bounceY();
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x, (hitbox.getSize().y / 2.f)));
	}

	//left side tp
	if (hitbox.getPosition().x < 0)
	{
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x + WINDOW_X * WINDOW_SCALE,
			hitbox.getPosition().y));
		if (currentPlatform == P_TOP_LEFT)
		{
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_TOP_RIGHT);
			activePlatforms[P_TOP_LEFT]--;
			activePlatforms[P_TOP_RIGHT]++;
		}
		else if (currentPlatform == P_LEFT_SIDE)
		{
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_RIGHT_SIDE_SMALL);
			activePlatforms[P_LEFT_SIDE]--;
			activePlatforms[P_RIGHT_SIDE_SMALL]++;
		}
	}

	//right side tp
	if (hitbox.getPosition().x > WINDOW_X * WINDOW_SCALE)
	{
		hitbox.setPosition(sf::Vector2f(0, hitbox.getPosition().y));

		if (currentPlatform == P_TOP_RIGHT)
		{
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_TOP_LEFT);
			activePlatforms[P_TOP_RIGHT]--;
			activePlatforms[P_TOP_LEFT]++;
		}
		else if (currentPlatform == P_RIGHT_SIDE_SMALL)
		{
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_LEFT_SIDE);
			activePlatforms[P_RIGHT_SIDE_SMALL]--;
			activePlatforms[P_LEFT_SIDE]++;
		}
	}


	if (currentPlatform == -1 && target >= 0) //gravity
		vel.y += .125 * (WINDOW_SCALE / 3.f);

	//animation speed
	speed = abs(vel.x) / SPEED_INC_X;

	if (currentPlatform >= 0 && frameCounter + speed * 2 >= 10)
	{
		sprite.nextFrame();
		frameCounter = 0;
		if (speed == 0)
			sprite.setFrame(3);
	}
	else
		frameCounter++;

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));

	sprite.setFaceRight(vel.x > 0);
	
}


void Enemy::setOnGround(float newYValue, int platform)
{
	Collidable::setOnGround(newYValue, platform);

	//sprite.setAnimation(AnimationNames::BOUNDER_GROUND);


	sprite.setPos(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y));
	sprite.setFaceRight(vel.x > 0);
#ifdef DEBUG
	std::cout << "enemy\n";
#endif // DEBUG
}


void Enemy::setPosition(sf::Vector2f newPos)
{
	hitbox.setPosition(newPos);
}


void Enemy::bounceSetLeft(Platform& platform)
{
	hitbox.setPosition(((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		+ platform.getPointPos(ConvexCorners::TOP_LEFT).x - 50, hitbox.getPosition().y);
}


void Enemy::bounceSetRight(Platform& platform)
{
	hitbox.setPosition((((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
		/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x + 50, hitbox.getPosition().y);
}


void Enemy::drawTo(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		window.draw(hitbox);
	sprite.drawTo(window);
}
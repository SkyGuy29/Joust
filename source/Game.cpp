#include "Game.h"


Game::Game()
{
	background.setImage("res/Art/joustSprite.png");
	background.setAnimation(AnimationNames::TEMP_BACKGROUND);
	background.setPos(sf::Vector2f(WINDOW_X * WINDOW_SCALE / 2.f + WINDOW_SCALE / 2.f, 
		WINDOW_Y * WINDOW_SCALE / 2.f)); //don't worry about it, it works guys
	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		platform[i].setPlatform(i, "a");
	}
}


void Game::update()
{
	player[0].update();
	for (const auto& i : platform)
	{
		collisionUpdate(&player[0], i);
	}
}


void Game::nextRound()
{
	currentRound++;

	if (currentRound % 5 == 1)
	{
		//normal round, this is placeholder for now lol
	}
	else if (currentRound % 5 == 2)
	{
		//survival round text
		//end of round 3000 point bonus if player did not die
		//I forgot how this worked in two player I think it's if one of them lives
	}
	else if (currentRound % 5 == 3 && currentRound != 3)
	{
		//beware of the "unbeatable?" pterodactyl
		//spawn a pterodactyl at the beginning of the round
	}
	else if (currentRound % 5 == 4 /* && two players */)
	{
		//gladiator round
		//bonus points awarded if you kill the other player :smiling_imp:
	}
	else if (currentRound % 5 == 0)
	{
		//egg round
	}
}


void Game::drawTo(sf::RenderWindow& window)
{
	background.drawTo(window);
	player[0].drawTo(window);
	for (auto& i : platform)
	{
		i.drawTo(window);
	}
}


//private


PlatformCollisionType Game::isTouching(sf::FloatRect hitbox, Platform platform)
{
	//y axis collision check
	if (hitbox.top <= platform.getPointPos(ConvexCorners::BOT_LEFT).y &&
		hitbox.top + hitbox.height >= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
	{
		//std::cout << "y-axis\n";
		//x axis general collision check 
		//still may not be a collision if outside the diagonal
		if (isTouchingX(hitbox, platform) == true)
		{
			if (hitbox.top <= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
			{ 
				if (hitbox.left >= platform.getPointPos(ConvexCorners::BOT_RIGHT).x)
				{
					if (hitbox.left <= ((hitbox.top + hitbox.height - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
						* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
						/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
						+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
						return PlatformCollisionType::TOP;
					else
						return PlatformCollisionType::RIGHT_HIGH;
				}
				//checks left diagonal
				else if (hitbox.left + hitbox.width <= platform.getPointPos(ConvexCorners::BOT_LEFT).x)
				{
					if ((hitbox.left + hitbox.width) >= ((hitbox.top + hitbox.height - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
						* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x))
						/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
						+ platform.getPointPos(ConvexCorners::TOP_LEFT).x)
						return PlatformCollisionType::TOP;
					else
						return PlatformCollisionType::LEFT_HIGH;
				}
				else
					return PlatformCollisionType::TOP;
			}
			//std::cout << "x-axis\n";
			//specific collision, determines behavior of interaction
			//checks right diagonal
			else if (hitbox.left >= platform.getPointPos(ConvexCorners::BOT_RIGHT).x)
			{
				if (hitbox.left <= ((hitbox.top - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
					/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
					return PlatformCollisionType::RIGHT;
			}
			//checks left diagonal
			else if (hitbox.left + hitbox.width <= platform.getPointPos(ConvexCorners::BOT_LEFT).x)
			{
				if ((hitbox.left + hitbox.width) >= ((hitbox.top - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
					* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x))
					/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
					+ platform.getPointPos(ConvexCorners::TOP_LEFT).x)
					return PlatformCollisionType::LEFT;
			}
			//on the bottom
			else
				return PlatformCollisionType::BOT;
		}
	}
	return PlatformCollisionType::NONE;
}



bool Game::isTouchingX(sf::FloatRect playerHitbox, Platform platform)
{
	if (playerHitbox.left <= platform.getPointPos(ConvexCorners::TOP_RIGHT).x &&
		playerHitbox.left + playerHitbox.width >= platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		return true;
	return false;
}


void Game::collisionUpdate(Collidable* collidable, Platform platform)
{
	switch (isTouching(collidable->getHitbox(), platform))
	{
	case PlatformCollisionType::TOP:
		collidable->setOnGround(platform.getPointPos(ConvexCorners::TOP_LEFT).y);
		break;
	case PlatformCollisionType::BOT:
		collidable->bounceY();
		collidable->setPosition(sf::Vector2f(collidable->getPosition().x, 
			platform.getPointPos(BOT_LEFT).y + (collidable->getSize().y / 2.f)));
		std::cout << "bot\n";
		break;
	case PlatformCollisionType::LEFT:
		collidable->bounceX();
		collidable->bounceSetLeft(platform);
		std::cout << "left\n";
		break;
	case PlatformCollisionType::LEFT_HIGH:
		collidable->bounceX();
		collidable->setPosition(sf::Vector2f(platform.getPointPos(TOP_LEFT).x - (collidable->getSize().x / 2.f), 
			collidable->getPosition().y));
		std::cout << "left high\n";
		break;
	case PlatformCollisionType::RIGHT:
		collidable->bounceX();
		collidable->bounceSetRight(platform);
		std::cout << "right\n";
		break;
	case PlatformCollisionType::RIGHT_HIGH:
		collidable->bounceX();
		collidable->setPosition(sf::Vector2f(platform.getPointPos(TOP_RIGHT).x + (collidable->getSize().x / 2.f), 
			collidable->getPosition().y));
		std::cout << "right high\n";
		break;
	case PlatformCollisionType::NONE:
		if (isTouchingX(collidable->getHitbox(), platform) == false)
			collidable->setOffGround();
	}
}

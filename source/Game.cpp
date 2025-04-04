#include "Game.h"


Game::Game()
{
	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		platform[i].setPlatform(i, "a");
	}// hohoho
	bridge.setSize(sf::Vector2f(WINDOW_X * WINDOW_SCALE, 3 * WINDOW_SCALE));
	bridge.setPosition(0, platform[PlatformNames::P_GROUND].getPointPos(ConvexCorners::TOP_LEFT).y);
	bridge.setFillColor(sf::Color(144, 72, 0));
	eggVec.emplace_back(new Egg);
	enemyVec.emplace_back(new Bounder);
	enemyVec.emplace_back(new Bounder);
	enemyVec.emplace_back(new Bounder);
	enemyVec.emplace_back(new Bounder);
	enemyVec.emplace_back(new Shadow);
	player[0].setPosition(sf::Vector2f(100, 100));
}


void Game::update()
{
	player[0].update();

	for (const auto& enemy : enemyVec)
		enemy->update(player);
	for (const auto& egg : eggVec)
		egg->update();

	for (auto& plat : platform)
		plat.update();

	collisionUpdate(&player[0], platform);
	for (const auto& egg : eggVec)
		collisionUpdate(egg, platform);

	for (const auto& enemy : enemyVec)
		collisionUpdate(enemy, platform);
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
	else if (currentRound == 3)
	{
		//burn the bridge
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
	window.draw(bridge);
	for (auto& i : platform)
		i.drawTo(window);
	for (auto& i : eggVec)
		i->drawTo(window);
	for (auto& i : enemyVec)
		i->drawTo(window);
	player[0].drawTo(window);
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
					
					return PlatformCollisionType::RIGHT_HIGH;
				}

				//checks left diagonal
				if (hitbox.left + hitbox.width <= platform.getPointPos(ConvexCorners::BOT_LEFT).x)
				{
					if ((hitbox.left + hitbox.width) >= ((hitbox.top + hitbox.height - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
						* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x))
						/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
						+ platform.getPointPos(ConvexCorners::TOP_LEFT).x)
						return PlatformCollisionType::TOP;
					
					return PlatformCollisionType::LEFT_HIGH;
				}
				
				return PlatformCollisionType::TOP;
			}
			//std::cout << "x-axis\n";
			//specific collision, determines behavior of interaction
			//checks right diagonal

			if (hitbox.left >= platform.getPointPos(ConvexCorners::BOT_RIGHT).x)
			{
				if (hitbox.left <= (hitbox.top - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
					/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
					return PlatformCollisionType::RIGHT;
			}
			//checks left diagonal
			else if (hitbox.left + hitbox.width <= platform.getPointPos(ConvexCorners::BOT_LEFT).x)
			{
				if (hitbox.left + hitbox.width >= (hitbox.top - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
					* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x)
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


bool Game::isTouchingEgg(sf::FloatRect, Egg)
{
	return false;
}


void Game::collisionUpdate(Collidable* collidable, Platform platform[])
{
	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		switch (isTouching(collidable->getHitbox(), platform[i]))
		{
		case PlatformCollisionType::TOP:
			collidable->setOnGround(platform[i].getPointPos(ConvexCorners::TOP_LEFT).y, i);
			break;
		case PlatformCollisionType::BOT:
			collidable->bounceY();
			collidable->setPosition(sf::Vector2f(collidable->getPosition().x,
				platform[i].getPointPos(BOT_LEFT).y + (collidable->getSize().y / 2.f)));
			std::cout << "bot\n";
			break;
		case PlatformCollisionType::LEFT:
			collidable->bounceX();
			collidable->bounceSetLeft(platform[i]);
			std::cout << "left\n";
			break;
		case PlatformCollisionType::LEFT_HIGH:
			collidable->bounceX();
			collidable->setPosition(sf::Vector2f(platform[i].getPointPos(ConvexCorners::TOP_LEFT).x - (collidable->getSize().x / 2.f),
				collidable->getPosition().y));
			std::cout << "left high\n";
			break;
		case PlatformCollisionType::RIGHT:
			collidable->bounceX();
			collidable->bounceSetRight(platform[i]);
			std::cout << "right\n";
			break;
		case PlatformCollisionType::RIGHT_HIGH:
			collidable->bounceX();
			collidable->setPosition(sf::Vector2f(platform[i].getPointPos(ConvexCorners::TOP_RIGHT).x + (collidable->getSize().x / 2.f),
				collidable->getPosition().y));
			std::cout << "right high\n";
			break;
		case PlatformCollisionType::NONE:
			//may need to change, the player is set off ground when screen wrapping
			if (collidable->getGrounded() >= 0 && collidable->getGrounded() < 8)
				if (collidable->getHitbox().left > platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_RIGHT).x ||
					collidable->getHitbox().left + collidable->getHitbox().width < platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_LEFT).x)
					collidable->setOffGround();
			break;
		}
	}
}

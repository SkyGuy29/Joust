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
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	enemyVec.emplace_back(new Shadow);
	player[0].setPosition(sf::Vector2f(100, 100));
}


void Game::update()
{
	static sf::Clock timer;
	//timer.restart();

	player[0].update();
	//std::cout << "update: " << timer.restart().asMilliseconds() / 1000. << '\n';

	for (int i = 0; i < enemyVec.size() - 1; i++)
	{
		for (int j = i + 1; j < enemyVec.size(); j++)
		{
			collisionUpdate(enemyVec.at(i), enemyVec.at(j));
		}
	}

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < enemyVec.size() - 1; j++)
		{
			collisionUpdate(&player[i], enemyVec.at(j));
		}

	for (const auto& enemy : enemyVec)
		enemy->update(player);
	for (const auto& egg : eggVec)
		egg->update();

	//std::cout << "EU: " << timer.restart().asMilliseconds() / 1000. << '\n';
	for (auto& plat : platform)
		plat.update();
	//std::cout << "P:LATupdate: " << timer.restart().asMilliseconds() / 1000. << '\n';

	collisionUpdate(&player[0], platform);
	//std::cout << "PLVP: " << timer.restart().asMilliseconds() / 1000. << '\n';
	
	for (const auto& egg : eggVec)
		collisionUpdate(egg, platform);
	//std::cout << "EGVP: " << timer.restart().asMilliseconds() / 1000. << '\n';

	for (const auto& enemy : enemyVec)
		collisionUpdate(enemy, platform);
	//std::cout << "ENVP: " << timer.restart().asMilliseconds() / 1000. << '\n';
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
PlatformCollisionType Game::isTouching(Collidable* collidable, Platform &platform)
{
	sf::FloatRect hitbox = collidable->getHitbox();

	//y axis collision check
	if (hitbox.top <= platform.getPointPos(ConvexCorners::BOT_LEFT).y &&
		hitbox.top + hitbox.height >= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
	{
		//std::cout << "y-axis\n";
		//x axis general collision check s
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



bool Game::isTouchingX(sf::FloatRect& playerHitbox, Platform& platform)
{
	if (playerHitbox.left <= platform.getPointPos(ConvexCorners::TOP_RIGHT).x &&
		playerHitbox.left + playerHitbox.width >= platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		return true;
	return false;
}


bool Game::isTouchingEgg(sf::FloatRect playerHitbox, Egg egg)
{
	return playerHitbox.intersects(egg.getHitbox());
}


void Game::collisionUpdate(Collidable* collidable, Platform platform[])
{
	static sf::Clock timer, timer2;
	//timer.restart();
	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		//timer2.restart();
		switch (isTouching(collidable, platform[i]))
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
			//std::cout << collidable->getGrounded() << std::endl;
			
			//std::cout << "CLTA: " << timer2.restart().asMilliseconds() /1000. << '\n';
			//may need to change, the player is set off ground when screen wrapping
			if (collidable->getGrounded() >= 0 && collidable->getGrounded() < 8)
			{
				
				//std::cout << "player left: " << collidable->getHitbox().left << std::endl;
				//std::cout << "platform right: " << platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_RIGHT).x << std::endl;
				//std::cout << ((float)(collidable->getHitbox().left) > (float)(platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_RIGHT).x)) << std::endl;
				if ((float)(collidable->getHitbox().left) > (float)(platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_RIGHT).x) || 
					collidable->getHitbox().left + collidable->getHitbox().width < platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_LEFT).x)
					collidable->setOffGround();
			}
			//std::cout << "CLTB: " << timer2.restart().asMilliseconds() / 1000. << '\n';
			break;
		}
	}
	//std::cout << "CLTC: " << timer2.restart().asMilliseconds() / 1000. << '\n';

	//std::cout << "COLLTMR: " << timer.restart().asMilliseconds() / 1000. << '\n';
}


void Game::collisionUpdate(Player* player, Enemy* enemy)
{
	sf::FloatRect nextPos;

	sf::FloatRect enemyBounds = enemy->getHitbox();
	sf::FloatRect playerBounds = player->getHitbox();

		nextPos = playerBounds;

		nextPos.left += player->getVelocity().x;
		nextPos.top += player->getVelocity().y;

		//if (playerBounds.left > wallBounds.left + 25)
			//wallBounds.left++;
		//else if (playerBounds.left + 50 < wallBounds.left)
			//wallBounds.left--;

		if (enemyBounds.intersects(nextPos))
		{
			std::cout << "DIE\n";
		}
}


void Game::collisionUpdate(Enemy* enemyOne, Enemy* enemyTwo)
{
	sf::FloatRect nextPos;

	sf::FloatRect enemyOneBounds = enemyOne->getHitbox();
	sf::FloatRect enemyTwoBounds = enemyTwo->getHitbox();

	nextPos = enemyOneBounds;

	nextPos.left += enemyOne->getVelocity().x;
	nextPos.top += enemyOne->getVelocity().y;

	//if (playerBounds.left > wallBounds.left + 25)
		//wallBounds.left++;
	//else if (playerBounds.left + 50 < wallBounds.left)
		//wallBounds.left--;

	if (enemyTwoBounds.intersects(nextPos))
	{
		enemyOne->bounceX();
		enemyTwo->bounceX();

		if (enemyOne->getPosition().y < enemyTwo->getPosition().y)
		{
			if (enemyOne->getVelocity().y > 0)
				enemyOne->addVelocity(0, -1);
			else
				enemyOne->addVelocity(0, enemyOne->getVelocity().y - 1);
		}
		else
		{
			if (enemyTwo->getVelocity().y > 0)
				enemyTwo->addVelocity(0, -1);
			else
				enemyTwo->addVelocity(0, enemyTwo->getVelocity().y - 1);
		}
	}
}

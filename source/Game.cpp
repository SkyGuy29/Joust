#include "Game.h"


Game::Game()
{
	for (int i = 0; i < PLATFORM_COUNT; i++)
		platform[i].setPlatform(i); // hohoho

	spawners[0].setPlatform(PlatformNames::P_TOP_MIDDLE);
	spawners[1].setPlatform(PlatformNames::P_LEFT_SIDE);
	spawners[2].setPlatform(PlatformNames::P_RIGHT_SIDE);
	spawners[3].setPlatform(PlatformNames::P_GROUND);

	lava.setSize(sf::Vector2f(WINDOW_X * WINDOW_SCALE, 26 * WINDOW_SCALE)); //numbers from sprite data
	lava.setPosition(0, (WINDOW_Y - 26) * WINDOW_SCALE);
	lava.setFillColor(sf::Color(248, 32, 0));

	livesAnim.setAnimation(P1_LIVES);
	livesAnim.setPos(sf::Vector2f(122 * WINDOW_SCALE, 213 * WINDOW_SCALE));

	livesText.setFont(font);
	livesText.setCharacterSize(15);
	livesText.setFillColor(sf::Color::Yellow);
	livesText.setString("0");
	livesText.setOrigin(livesText.getLocalBounds().width / 2,
		livesText.getLocalBounds().height / 2); //AS IF I KNOW WHY I NEED TO ADD EXACTLY 4.8 PIXELS
	livesText.setScale(WINDOW_SCALE, WINDOW_SCALE);
	livesText.setPosition(127 * WINDOW_SCALE, 204.5 * WINDOW_SCALE);

	font.loadFromFile("res/Fonts/Arcade.ttf");
	font.setSmooth(false);
	scoreText.setFont(font);
	scoreText.setCharacterSize(15);
	scoreText.setFillColor(sf::Color::Yellow);
	scoreText.setString("0");
	scoreText.setOrigin(scoreText.getLocalBounds().width / 2, 
		scoreText.getLocalBounds().height / 2 + 4.8); //AS IF I KNOW WHY I NEED TO ADD EXACTLY 4.8 PIXELS
	scoreText.setScale(WINDOW_SCALE, WINDOW_SCALE);
	scoreText.setPosition(104 * WINDOW_SCALE, 213 * WINDOW_SCALE);
	topScore.setFont(font);
	topScore.setCharacterSize(15);
	topScore.setFillColor(sf::Color::Yellow);
	topScore.setString("Top Score: 999");
	topScore.setOrigin(topScore.getLocalBounds().width / 2,
		topScore.getLocalBounds().height / 2 + 4.8);
	topScore.setScale(WINDOW_SCALE, WINDOW_SCALE);
	topScore.setPosition(204 * WINDOW_SCALE, 213 * WINDOW_SCALE); //fix position

	player[0].setPosition(sf::Vector2f(166 * WINDOW_SCALE, 166 * WINDOW_SCALE));
}


void Game::update()
{
	player[0].update(activePlatforms);

	//death to lava
	if (player[0].getPosition().y >= 210 * WINDOW_SCALE)
	{
		player->resetVelocityX();
		player->resetVelocityY();
		player->toggleGravity(false);
		player->toggleDisable(true);

		const int randPlat = choosePlatform();
		player->setRespawn(randPlat);
		if (randPlat != -1)
		{
			spawners[randPlat].setSpawnAnim(AnimationNames::P1_SPAWN_PLAT);
			spawners[randPlat].setEnabled(true);
		}

		lives--;
	}

	//enemy-enemy interaction
	if (enemyVec.size() > 1)
		for (int i = 0; i < enemyVec.size() - 1; i++)
			for (int j = i + 1; j < enemyVec.size(); j++)
				collisionUpdate(enemyVec.at(i), enemyVec.at(j));

	//player-enemy interaction
	for (auto& i : player)
		for (int j = 0; j < enemyVec.size(); j++)
			collisionUpdate(&i, enemyVec.at(j), j);

	for (const auto& enemy : enemyVec) //enemy updates
		enemy->update(player, activePlatforms);
	for (const auto& egg : eggVec) //egg updates
		egg->update();

	for (auto& plat : platform) //platform updates
		plat.update();

	//player-platform interaction
	collisionUpdate(&player[0], platform);

	//egg-platform interaction
	for (const auto& egg : eggVec)
		collisionUpdate(egg, platform);

	//enemy-platform interaction
	for (const auto& enemy : enemyVec)
		collisionUpdate(enemy, platform);

	//egg collection update
	for (int i = 0; i < eggVec.size(); i++) 
	{
		if (isTouching(player[0].getHitbox(), eggVec.at(i)))
		{
			eggsCollected++;
			if (eggsCollected < 4)
				score[0] += eggsCollected * 250;
			else
				score[0] += 1000;

			eggVec.erase(eggVec.begin()+i); //fix later to remove the specific egg collected
		}
	}

	const int randPlat = choosePlatform();

	//spawns player once there is an active platform
	if (player[0].getDisable() && !player[0].getRespawning() && countActivePlatforms() > 0)
	{
		player[0].setRespawn(randPlat);
		spawners[randPlat].setSpawnAnim(AnimationNames::P1_SPAWN_PLAT);
		spawners[randPlat].setEnabled(true);
	}

	//new round enemy spawning
	if (randPlat != -1 && spawnCredits > 4)
	{
		if (enemyVec.empty())
			spawnEnemy(randPlat);
		else if (!enemyVec.at(enemyVec.size() - 1)->getSpawn())
			spawnEnemy(randPlat);
	}

	//extra life when you get 20k points
	if (score[0] >= goalScore)
	{
		if (lives < 5)
			lives++;
		
		goalScore += 20000;
	}

	//egg hatch update
	for (int i = 0; i < eggVec.size(); i++)
	{
		if (eggVec.at(i)->getTimer() >= 20000)
		{
			switch (eggVec.at(i)->getType())
			{
			case EMPTY:
				enemyVec.emplace_back(new Bounder(eggVec.at(i)->getHitbox().getPosition()));
				break;
			case BOUNDER:
				enemyVec.emplace_back(new Hunter(eggVec.at(i)->getHitbox().getPosition()));
				break;
			case HUNTER:
				enemyVec.emplace_back(new Shadow(eggVec.at(i)->getHitbox().getPosition()));
				break;
			case SHADOW:
				enemyVec.emplace_back(new Shadow(eggVec.at(i)->getHitbox().getPosition()));
				break;
			}
			eggVec.erase(eggVec.begin() + i);
		}
	}

	if (eggVec.empty() && enemyVec.empty())
		nextRound();
	else
		std::cout << "Eggs: " << eggVec.size() << " Enemies: " << enemyVec.size() << " AC: " << countActivePlatforms() << std::endl;

	//spawners update
	for (auto& spawner : spawners)
		spawner.update();

	//text updates
	livesText.setString(std::to_string(lives));
	scoreText.setString(std::to_string(score[0]));
	scoreText.setOrigin(scoreText.getLocalBounds().width - scoreText.getCharacterSize() / 2,
		scoreText.getLocalBounds().height / 2 + 4.8);
	topScore.setString(std::to_string(score[0]));
	topScore.setOrigin(scoreText.getLocalBounds().width - topScore.getCharacterSize() / 2,
		topScore.getLocalBounds().height / 2 + 4.8);
}


void Game::nextRound()
{
	int variationSum = 0;
	currentRound++;

	//gives some variety to the spawn credits
	for (int i = 0; i < currentRound; i++)
		variationSum += rand() % 5 * 0.5;

	//10 is base, increases by 10% every round base then adds variation
	spawnCredits = 10 * currentRound * 1.1 + variationSum;

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
	window.draw(lava);
	for (auto& i : platform)
		i.drawTo(window);
	for (const auto& i : eggVec)
		i->drawTo(window);
	for (const auto& i : enemyVec)
		i->drawTo(window);
	for (auto& i : spawners)
		i.drawTo(window);

	player[0].drawTo(window);

	livesAnim.drawTo(window);
	window.draw(livesText);
	window.draw(scoreText);
	window.draw(topScore);
}


//private
void Game::spawnEnemy(int randPlat)
{
	if (currentRound >= 6 && spawnCredits >= 64)
	{
		spawnCredits -= 64;
		enemyVec.emplace_back(new Shadow);
		enemyVec.at(enemyVec.size() - 1)->setSpawn(randPlat);
		spawners[randPlat].setSpawnAnim(AnimationNames::ENEMY_SPAWN_PLAT);
		spawners[randPlat].setEnabled(true);
	}
	else if (currentRound >= 3 && currentRound < 25 && spawnCredits >= 15)
	{
		spawnCredits -= 15;
		enemyVec.emplace_back(new Hunter);
		enemyVec.at(enemyVec.size() - 1)->setSpawn(randPlat);
		spawners[randPlat].setSpawnAnim(AnimationNames::ENEMY_SPAWN_PLAT);
		spawners[randPlat].setEnabled(true);
	}
	else if (currentRound < 11 && spawnCredits >= 4)
	{
		spawnCredits -= 4;
		enemyVec.emplace_back(new Bounder);
		enemyVec.at(enemyVec.size() - 1)->setSpawn(randPlat);
		spawners[randPlat].setSpawnAnim(AnimationNames::ENEMY_SPAWN_PLAT);
		spawners[randPlat].setEnabled(true);
	}

	std::cout << currentRound << std::endl;
	std::cout << spawnCredits << std::endl;
}


PlatformCollisionType Game::isTouching(Collidable* collidable, Platform& platform)
{
	sf::FloatRect hitbox = collidable->getHitbox();

	//y axis collision check
	if (hitbox.top <= platform.getPointPos(ConvexCorners::BOT_LEFT).y &&
		hitbox.top + hitbox.height >= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
	{
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
	

bool Game::isTouching(sf::FloatRect playerHitbox, Egg *egg)
{
	return playerHitbox.intersects(egg->getHitbox());
}


void Game::collisionUpdate(Collidable* collidable, Platform platform[])
{
	static sf::Clock timer, timer2;
	//timer.restart();
	if (!collidable)
		return;
	for (int i = 0; i < PLATFORM_COUNT; i++)
	{
		//timer2.restart();
		switch (isTouching(collidable, platform[i]))
		{
		case PlatformCollisionType::TOP:
			if (collidable->getGrounded() == -1 && !dynamic_cast<Egg*>(collidable))
			{
				activePlatforms[i]++;
			}
			collidable->setOnGround(platform[i].getPointPos(ConvexCorners::TOP_LEFT).y, i);
			break;
		case PlatformCollisionType::BOT:
			collidable->bounceY();
			collidable->setPosition(sf::Vector2f(collidable->getPosition().x,
				platform[i].getPointPos(BOT_LEFT).y + (collidable->getSize().y / 2.f)));
			break;
		case PlatformCollisionType::LEFT:
			collidable->bounceX();
			collidable->bounceSetLeft(platform[i]);
			break;
		case PlatformCollisionType::LEFT_HIGH:
			collidable->bounceX();
			collidable->setPosition(sf::Vector2f(platform[i].getPointPos(ConvexCorners::TOP_LEFT).x - (collidable->getSize().x / 2.f),
				collidable->getPosition().y));
			break;
		case PlatformCollisionType::RIGHT:
			collidable->bounceX();
			collidable->bounceSetRight(platform[i]);
			break;
		case PlatformCollisionType::RIGHT_HIGH:
			collidable->bounceX();
			collidable->setPosition(sf::Vector2f(platform[i].getPointPos(ConvexCorners::TOP_RIGHT).x + (collidable->getSize().x / 2.f),
				collidable->getPosition().y));
			break;
		case PlatformCollisionType::NONE:
			//may need to change, the player is set off ground when screen wrapping
			if (collidable->getGrounded() >= 0 && collidable->getGrounded() < 8)
			{
				if ((float)(collidable->getHitbox().left) > (float)(platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_RIGHT).x) ||
					collidable->getHitbox().left + collidable->getHitbox().width < platform[collidable->getGrounded()].getPointPos(ConvexCorners::TOP_LEFT).x)
				{
					if (!dynamic_cast<Egg*>(collidable))
						activePlatforms[collidable->getGrounded()]--;
					collidable->setOffGround();
				}
			}
			break;
		}
	}
}


void Game::collisionUpdate(Player* player, Enemy* enemy, int pos)
{
	sf::FloatRect enemyBounds = enemy->getHitbox(),
	playerBounds = player->getHitbox(), nextPos = playerBounds;

	nextPos.left += player->getVelocity().x;
	nextPos.top += player->getVelocity().y;

	if (enemyBounds.intersects(nextPos))
	{
		//enemy death
		if (enemy->getPosition().y > player->getPosition().y)
		{
			eggVec.emplace_back(new Egg(enemy->getPosition(), enemy->getVelocity(), enemy->getType()));
			enemyVec.erase(enemyVec.begin() + pos);
			player->resetVelocityY();
			player->addVelocity(0, -2);
			if (dynamic_cast<Bounder*>(enemy))
				score[0] += 250;
			else if (dynamic_cast<Hunter*>(enemy))
				score[0] += 750;
			else if (dynamic_cast<Shadow*>(enemy))
				score[0] += 1500;
		}
		//player death
		else if (enemy->getPosition().y < player->getPosition().y)
		{
			//disable player
			player->resetVelocityX();
			player->resetVelocityY();
			player->toggleGravity(false);
			player->toggleDisable(true);
			 
			const int randPlat = choosePlatform();
			player->setRespawn(randPlat);
			if (randPlat == -1)
				return;
			spawners[randPlat].setSpawnAnim(AnimationNames::P1_SPAWN_PLAT);
			spawners[randPlat].setEnabled(true);

			enemy->resetVelocityY();
			enemy->addVelocity(0, -2);

			lives--;
		}
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
		if (enemyOne->getPosition().y + enemyOne->getSize().y / 2 < enemyTwo->getPosition().y )
		{
				enemyOne->resetVelocityY();
				//enemyOne->setPosition(sf::Vector2f(enemyOne->getPosition().x, enemyOne->getPosition().y));
				enemyOne->addVelocity(0, -2);
				enemyTwo->resetVelocityY();
				enemyTwo->setPosition(sf::Vector2f(enemyTwo->getPosition().x, enemyOne->getPosition().y + enemyOne->getSize().y));
				enemyTwo->addVelocity(0, 2);
			
		}
		else if (enemyTwo->getPosition().y + enemyTwo->getSize().y / 2 < enemyOne->getPosition().y)
		{
			enemyTwo->resetVelocityY();
			//enemyTwo->setPosition(sf::Vector2f(enemyTwo->getPosition().x, enemy->getPosition().y));
			enemyTwo->addVelocity(0, -2);
			enemyOne->resetVelocityY();
			enemyOne->setPosition(sf::Vector2f(enemyOne->getPosition().x, enemyTwo->getPosition().y + enemyTwo->getSize().y));
			enemyOne->addVelocity(0, 2);
		}
		else
		{
			enemyOne->bounceX();
			enemyTwo->bounceX();
		}
	}
}


int Game::countActivePlatforms()
{
	activePlatCount = 4;

	//count active platforms
	for (int i = 0; i < PLATFORM_COUNT; i++)
		if (i == P_TOP_MIDDLE || i == P_LEFT_SIDE || i == P_RIGHT_SIDE || i == P_GROUND)
			if (activePlatforms[i] > 0)
				activePlatCount--;

	return activePlatCount;
}


int Game::choosePlatform()
{
	//randomize
	int randPlat, activePlatCount = countActivePlatforms(), platNum = 0;

	if (activePlatCount != 0)
		randPlat = rand() % activePlatCount;
	else 
		return -1;

	//pick the spawn platform that corresponds to the random number
	//if a platform has enemies on it, we skip it
	if (activePlatforms[P_TOP_MIDDLE] == 0)
		if (randPlat == platNum++)
			return 0;

	if (activePlatforms[P_LEFT_SIDE] == 0)
		if (randPlat == platNum++)
			return 1;

	if (activePlatforms[P_RIGHT_SIDE] == 0)
		if (randPlat == platNum++)
			return 2;

	if (activePlatforms[P_GROUND] == 0)
		if (randPlat == platNum)
			return 3;

	return -1;
}

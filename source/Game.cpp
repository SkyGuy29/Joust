#include "Game.h"


void Game::update()
{
	player[0].update();
	switch (isTouching(player[0].getHitbox(), platform))
	{
	case PlatformCollisionType::LEFT:
		std::cout << "left\n";
		break;
	case PlatformCollisionType::RIGHT:
		std::cout << "right\n";
		break;
	case PlatformCollisionType::TOP:
		std::cout << "top\n";
		break;
	case PlatformCollisionType::BOT:
		std::cout << "bot\n";
		break;
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
		//end of round 3000 point bonus if player did not not die
		//i forgot how this worked in two player i think its if one of them lives
	}
	else if (currentRound % 5 == 3 && currentRound != 3)
	{
		//beware of the “unbeatable?” pterodactyl
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
	player[0].drawTo(window);
	platform.drawTo(window);
}


//private


PlatformCollisionType Game::isTouching(sf::FloatRect playerHitbox, Platform platform)
{
	//y axis collision check
	if (playerHitbox.top <= platform.getPointPos(ConvexCorners::BOT_LEFT).y &&
		playerHitbox.top + playerHitbox.height >= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
	{
		//std::cout << "y-axis\n";
		//x axis general collision check 
		//still may not be a collision if outside the diagonal
		if (playerHitbox.left <= platform.getPointPos(ConvexCorners::TOP_RIGHT).x &&
			playerHitbox.left + playerHitbox.width >= platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		{
			if (playerHitbox.top <= platform.getPointPos(ConvexCorners::TOP_LEFT).y)
			{ 
				return PlatformCollisionType::TOP;
			}
			//std::cout << "x-axis\n";
			//specific collision, detirmines behavior of interaction
			//checks right diagonal
			else if (playerHitbox.left >= platform.getPointPos(ConvexCorners::BOT_RIGHT).x)
			{
				if (playerHitbox.left <= ((playerHitbox.top - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
					/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
					+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
					return PlatformCollisionType::RIGHT;
			}
			//checks left diagonal
			else if (playerHitbox.left + playerHitbox.width <= platform.getPointPos(ConvexCorners::BOT_LEFT).x)
			{
				if ((playerHitbox.left + playerHitbox.width) >= ((playerHitbox.top - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
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
	//std::cout << "none";
}
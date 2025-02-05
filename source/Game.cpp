#include "Game.h"


void Game::update()
{
	player[0].update();
	isTouching(player[0].getHitbox(), platform.getHitbox());
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


PlatformCollisionType Game::isTouching(sf::FloatRect playerHitbox, sf::ConvexShape platformHitbox)
{
	//y axis collision check
	if (playerHitbox.top <= platformHitbox.getPoint(ConvexCorners::BOT_LEFT).y &&
		playerHitbox.top + playerHitbox.height >= platformHitbox.getPoint(ConvexCorners::TOP_LEFT).y)
	{
		std::cout << "y-axis";
		//x axis general collision check 
		//still may not be a collision if outside the diagonal
		if (playerHitbox.left <= platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).x &&
			playerHitbox.left + playerHitbox.width >= platformHitbox.getPoint(ConvexCorners::TOP_LEFT).x)
		{
			std::cout << "x-axis";
			//specific collision, detirmines behavior of interaction
			//checks right diagonal
			if (playerHitbox.left >= platformHitbox.getPoint(ConvexCorners::BOT_RIGHT).x)
				if (playerHitbox.left >= ((playerHitbox.top - platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).y)
					* (platformHitbox.getPoint(ConvexCorners::BOT_RIGHT).x - platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).x))
					/ (platformHitbox.getPoint(ConvexCorners::BOT_RIGHT).y - platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).y)
					+ platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).x)
					//return PlatformCollisionType::RIGHT;
					std::cout << "Right";
			//checks left diagonal
				else if (playerHitbox.left + playerHitbox.width <= platformHitbox.getPoint(ConvexCorners::BOT_LEFT).x)
					if ((playerHitbox.left + playerHitbox.width) >= ((playerHitbox.top - platformHitbox.getPoint(ConvexCorners::TOP_LEFT).y)
						* (platformHitbox.getPoint(ConvexCorners::BOT_LEFT).x - platformHitbox.getPoint(ConvexCorners::TOP_LEFT).x))
						/ (platformHitbox.getPoint(ConvexCorners::BOT_LEFT).y - platformHitbox.getPoint(ConvexCorners::TOP_LEFT).y)
						+ platformHitbox.getPoint(ConvexCorners::TOP_LEFT).x)
						std::cout << "left";
					//return PlatformCollisionType::LEFT; 
			//on the bottom
			else
				;
		}
	}
	std::cout << "none";
	return PlatformCollisionType::LEFT;
}
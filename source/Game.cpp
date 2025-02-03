#include "Game.h"


void Game::update()
{
	player[0].update();
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


PlatformCollisionType Game::isTouching(sf::IntRect playerHitbox, sf::ConvexShape platformHitbox)
{
	//y axis collision check
	if (playerHitbox.top <= platformHitbox.getPoint(ConvexCorners::BOT_LEFT).y &&
		playerHitbox.top + playerHitbox.height >= platformHitbox.getPoint(ConvexCorners::TOP_LEFT).y)
	{
		//x axis general collision check 
		//still may not be a collision if outside the diagonal
		if (playerHitbox.left <= platformHitbox.getPoint(ConvexCorners::TOP_RIGHT).x &&
			playerHitbox.left + playerHitbox.width >= platformHitbox.getPoint(ConvexCorners::TOP_LEFT).x)
		{
			//specific collision, detirmines behavior of interaction
			//checks right diagonal
			if (playerHitbox.left >= platformHitbox.getPoint(ConvexCorners::BOT_RIGHT).x)
				return PlatformCollisionType::RIGHT;
			//checks left diagonal
			else if (playerHitbox.left + playerHitbox.width <= platformHitbox.getPoint(ConvexCorners::BOT_LEFT).x)
				return PlatformCollisionType::LEFT;
			//on the bottom
			else
				;
		}
	}
}
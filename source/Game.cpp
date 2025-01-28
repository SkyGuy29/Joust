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
}

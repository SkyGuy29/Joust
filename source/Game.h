#pragma once
#include "Player.h"


//handles the actual gameplay of joust, not the intro, leaderboard, stuff like that.
class Game
{
public:
	//Game();
	void update();
	void nextRound();
private:
	int score, lives, currentRound;
	Player player[2]; //or just make two variables?
	//enemies
	//eggs
	//birds for the eggs
	//
};


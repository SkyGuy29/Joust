#pragma once
#include "Player.h"
#include "Platform.h"


//handles the actual gameplay of joust, not the intro, leaderboard, stuff like that.
class Game
{
public:
	Game();
	void update();
	void nextRound();

	void drawTo(sf::RenderWindow&);

private:
	//handles collision
	PlatformCollisionType isTouching(sf::FloatRect, Platform);
	void isTouchingBounds();
	bool isTouchingX(sf::FloatRect, Platform);


	int score, lives, currentRound;
	Player player[2]; //or just make two variables?

	Platform platform = Platform(0, "a");
	Animation background;
	//enemies
	//eggs
	//birds for the eggs
	//
};

// okay
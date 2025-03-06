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
	bool isTouchingX(sf::FloatRect, Platform);
	void collisionUpdate(Collidable*, Platform[]);

	int score = 0, lives = 5, currentRound = 1, currentFloor = -1;
	Player player[2]; //or just make two variables?

	Platform platform[8];
	Animation background;
	//enemies
	//eggs
	//birds for the eggs
};

// okay
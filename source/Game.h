#pragma once
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Egg.h"
#include "enemyTypes/Bounder.h"
#include "enemyTypes/Hunter.h"
#include "enemyTypes/Shadow.h"


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
	bool isTouchingEgg(sf::FloatRect, Egg);
	void collisionUpdate(Collidable*, Platform[]);

	int score[2] {}, lives = 5, currentRound = 1;
	Player player[2]; //or just make two variables?

	std::vector<Enemy*> enemyVec;
	Platform platform[8];
	sf::RectangleShape bridge;
	//enemies
	//eggs
	std::vector<Egg*> eggVec;
	//birds for the eggs
};

// okay
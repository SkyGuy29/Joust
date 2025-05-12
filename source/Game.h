#pragma once
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Egg.h"
#include "Spawner.h"
#include "enemyTypes/Bounder.h"
#include "enemyTypes/Hunter.h"
#include "enemyTypes/Shadow.h"


//handles the actual gameplay of joust, not the intro, leaderboard, stuff like that.
class Game
{
public:
	Game();
	~Game();
	void update();
	void nextRound();

	void drawTo(sf::RenderWindow&);

private:
	//handles collision
	void spawnEnemy(int);
	PlatformCollisionType isTouching(Collidable*, Platform&);
	bool isTouching(sf::FloatRect, Egg*);
	bool isTouchingX(sf::FloatRect&, Platform&);
	void collisionUpdate(Collidable*, Platform[]);
	void collisionUpdate(Player*, Enemy*, int);
	void collisionUpdate(Enemy*, Enemy*);
	int countActivePlatforms();
	int choosePlatform();

	int score[2]{}, lives = 4, currentRound = 1, eggsCollected = 0, activePlatforms[PlatformNames::PLATFORM_COUNT] = {},
		activePlatCount = 4, goalScore = 20000;
	float spawnCredits = 10;
	Player player[2]; //potential implementation for 2 player mode, same with the score

	std::vector<Enemy*> enemyVec;
	std::vector<Egg*> eggVec;
	Platform platform[8];
	sf::RectangleShape lava;
	sf::Font font;
	Animation livesAnim;
	sf::Text livesText, //holds the number of lives left. todo: make array for 2p
	scoreText, topScore; //holds the top score until the game is shut off, displays it on the right.
	//todo: remove topScore when leaderboard is added

	Spawner spawners[4];
	//eventually add birds for the eggs
};

// okay
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
	void update();
	void nextRound();

	void drawTo(sf::RenderWindow&);

private:
	//handles collision
	PlatformCollisionType isTouching(Collidable*, Platform&);
	bool isTouching(sf::FloatRect, Egg*);
	bool isTouchingX(sf::FloatRect&, Platform&);
	void collisionUpdate(Collidable*, Platform[]);
	void collisionUpdate(Player*, Enemy*, int);
	void collisionUpdate(Enemy*, Enemy*);
	void choosePlatform(Collidable*);

	int score[2]{}, lives = 5, currentRound = 1, eggsCollected = 0, activePlatforms[PlatformNames::PLATFORM_COUNT] = {};
	Player player[2]; //or just make two variables?

	std::vector<Enemy*> enemyVec;
	std::vector<Egg*> eggVec;
	Platform platform[8];
	sf::RectangleShape bridge;
	sf::Font font;
	sf::Text scoreText; //todo: make array for 2p
	sf::Text topScore; //holds the top score until the game is shut off, displays it on the right. todo: remove when leaderboard is added

	Spawner spawners[4];
	//eventually add birds for the eggs
};

// okay
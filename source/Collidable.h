#pragma once
#include "globals.hpp"
#include "Platform.h"


class Collidable
{
public:
	//updates the collidable once, meant to be called every frame
	virtual void update() {}
	
	virtual void setOnGround(float, int);
	virtual void setOffGround() { currentPlatform = -1; }
	virtual int getGrounded() { return currentPlatform; }

	//flips the velocity of the collidable horizontally
	virtual void bounceX() { vel.x *= -1; }

	//flips the velocity of the collidable vertically
	virtual void bounceY() { vel.y *= -1; }

	//repositions the hitbox based on the formula given in res\misc\diagonalCollisionDerivationP2.png
	virtual void bounceSetLeft(Platform&);
	virtual void bounceSetRight(Platform&);
	virtual void setPosition(const sf::Vector2f newPos) { hitbox.setPosition(newPos); }

	sf::Vector2f getPosition() const { return hitbox.getPosition(); }
	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getSize() const { return hitbox.getSize(); }

	const sf::FloatRect& getHitbox() const { return hitbox.getGlobalBounds(); }
	 
protected:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	int currentPlatform = -1;
};
#pragma once
#include "globals.hpp"
#include "Platform.h"


class Collidable
{
public:
	virtual void update() {}
	virtual void setOnGround(float, int);
	virtual void setOffGround() { onGround = -1; }
	virtual int getGrounded() { return onGround; }
	virtual void bounceX() { vel.x *= -1; }
	virtual void bounceY() { vel.y *= -1; }
	virtual void bounceSetLeft(Platform);
	virtual void bounceSetRight(Platform);
	virtual void setPosition(const sf::Vector2f newPos) { hitbox.setPosition(newPos); }

	sf::Vector2f getPosition() const { return hitbox.getPosition(); }
	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getSize() const { return hitbox.getSize(); }

	sf::FloatRect getHitbox() const { return hitbox.getGlobalBounds(); }
	 
protected:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	int onGround = -1;
};
#pragma once
#include "globals.hpp"
#include "Platform.h"


class Collidable
{
public:
	virtual void update() {}
	void setOnGround(float);
	void bounceX() { vel.x *= -1; }
	void bounceY() { vel.y *= -1; }
	void bounceSetLeft(Platform);
	void bounceSetRight(Platform);
	void setOffGround() { onGround = false; }
	void setPosition(sf::Vector2f newPos) { hitbox.setPosition(newPos); }

	sf::Vector2f getPosition() const { return hitbox.getPosition(); }
	sf::Vector2f getVelocity() const { return vel; }
	sf::Vector2f getSize() const { return hitbox.getSize(); }

	sf::FloatRect getHitbox() const { return hitbox.getGlobalBounds(); }
	 
protected:
	sf::Vector2f vel;

	sf::RectangleShape hitbox;

	bool onGround = false;
};
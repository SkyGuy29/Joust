#pragma once
#include "Animation.h"


class Platform
{
public:
	Platform();
	~Platform();

	void setPlatform(const int, std::string);

	sf::ConvexShape getHitbox() const { return hitbox; }
	
	sf::Vector2f getPointPos(const ConvexCorners corner) const 
	{ 
		return hitbox.getPoint(corner) + hitbox.getPosition();
	}

	void drawTo(sf::RenderWindow&) const;

private:
	sf::ConvexShape hitbox;

	bool destroyed = false;
	Animation sprite;
};


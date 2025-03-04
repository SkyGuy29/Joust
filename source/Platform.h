#pragma once
#include "Globals.hpp"

class Platform
{
public:
	Platform();
	~Platform();

	void setPlatform(int, std::string);

	sf::ConvexShape getHitbox() const { return hitbox; }
	
	sf::Vector2f getPointPos(ConvexCorners corner) const 
	{ 
		return hitbox.getPoint(corner) + hitbox.getPosition();
	}

	void drawTo(sf::RenderWindow&);

private:
	sf::ConvexShape hitbox;

	bool destroyed = false;
	sf::Sprite sprite;
	sf::Texture img;

};


#include "Platform.h"


Platform::Platform(int platformID, std::string file)
{
	hitbox.setPointCount(4);
	hitbox.setOrigin(0, 0);
	hitbox.setFillColor(sf::Color::Red);
	switch (platformID)
	{
	case 0:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0, 0));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(500, 0));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(200, 100));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(100, 100));
		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	}

	img.loadFromFile(file);
	sprite.setTexture(img);
	hitbox.setPosition(300, 300);
}


Platform::~Platform()
{

}


void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
}

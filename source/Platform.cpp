#include "Platform.h"


Platform::Platform(int platformID, std::string file)
{
	hitbox.setPointCount(4);
	hitbox.setOrigin(0, 0);
	hitbox.setFillColor(sf::Color::Red);
	switch (platformID)
	{
	case 0:
		hitbox.setPoint(0, sf::Vector2f(0, 0));
		hitbox.setPoint(1, sf::Vector2f(300, 0));
		hitbox.setPoint(2, sf::Vector2f(250, 50));
		hitbox.setPoint(3, sf::Vector2f(50, 50));
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


sf::ConvexShape Platform::getHitbox()
{
	return hitbox;
}


void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
}

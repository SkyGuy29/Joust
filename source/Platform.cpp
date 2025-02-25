#include "Platform.h"


Platform::Platform(int platformID, std::string file)
{
	hitbox.setPointCount(4);
	hitbox.setOrigin(0, 0);
	hitbox.setFillColor(sf::Color::Red);
	switch (platformID)
	{
	case 0: //top middle
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(65 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(134 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(130 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(78 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		break;
	case 1: //right side
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(158 * WINDOW_SCALE, 83 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(203 * WINDOW_SCALE, 83 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(194 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(178 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		break;
	case 2: //right side small (UNFINISHED)
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(65 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(134 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(130 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(78 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		break;
	case 3: //left side
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(48 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(39 * WINDOW_SCALE, 96 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(11 * WINDOW_SCALE, 96 * WINDOW_SCALE));
		break;
	case 4: //bottom middle
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(81 * WINDOW_SCALE, 114 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(131 * WINDOW_SCALE, 114 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(120 * WINDOW_SCALE, 120 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(92 * WINDOW_SCALE, 120 * WINDOW_SCALE));
		break;
	case 5: //top left (UNFINISHED)
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(65 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(134 * WINDOW_SCALE, 40 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(130 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(78 * WINDOW_SCALE, 48 * WINDOW_SCALE));
		break;
	}

	img.loadFromFile(file);
	sprite.setTexture(img);
}


Platform::~Platform()
{

}


void Platform::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
}

#include "Platform.h"


Platform::Platform()
{
	hitbox.setPointCount(4);
	hitbox.setOrigin(0, 0);
	hitbox.setFillColor(sf::Color::Red);
}


Platform::~Platform() = default;


void Platform::setPlatform(int platformID, std::string file)
{
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
	case 2: //right side small
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(201 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(235 * WINDOW_SCALE, 91 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(220 * WINDOW_SCALE, 96 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(205 * WINDOW_SCALE, 96 * WINDOW_SCALE));
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
	case 5: //top left
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0 * WINDOW_SCALE, 29 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(23 * WINDOW_SCALE, 29 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(16 * WINDOW_SCALE, 33 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(0 * WINDOW_SCALE, 33 * WINDOW_SCALE));
		break;
	case 6: //top right
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(198 * WINDOW_SCALE, 29 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(235 * WINDOW_SCALE, 29 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(235 * WINDOW_SCALE, 33 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(204 * WINDOW_SCALE, 33 * WINDOW_SCALE));
		break;
	case 7: //ground
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(39 * WINDOW_SCALE, 157 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(187 * WINDOW_SCALE, 157 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(177 * WINDOW_SCALE, 169 * WINDOW_SCALE));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(47 * WINDOW_SCALE, 169 * WINDOW_SCALE));
		break;
	}

	img.loadFromFile(file);
	sprite.setTexture(img);
}


void Platform::drawTo(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		window.draw(hitbox);
}

#include "Platform.h"


Platform::Platform()
{
	hitbox.setPointCount(4);
	hitbox.setOrigin(0, 0);
	hitbox.setFillColor(sf::Color::Red);
}


Platform::~Platform() = default;


void Platform::setPlatform(const int platformID, std::string file)
{
	//loading raw hitbox pixel data
	switch (platformID)
	{
	case 0: //top middle
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(65, 40));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(134, 40));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(115, 48));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(78, 48));
		break;
	case 1: //right side
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(158, 83));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(203, 83));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(194, 91));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(178, 91));
		break;
	case 2: //right side small
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(201, 91));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(235, 91));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(220, 96));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(205, 96));
		break;
	case 3: //left side
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0, 91));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(48, 91));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(39, 96));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(11, 96));
		break;
	case 4: //bottom middle
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(81, 114));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(131, 114));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(120, 120));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(92, 120));
		break;
	case 5: //top left
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0, 29));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(23, 29));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(16, 33));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(0, 33));
		break;
	case 6: //top right
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(198, 29));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(235, 29));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(235, 33));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(204, 33));
		break;
	case 7: //ground
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(39, 157));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(187, 157));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(177, 169));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(47, 169));
		break;
	}

	//offsetting hitboxes to fit the window scale and be positioned correctly
	//there definitely is a mathematical way to do this but that would just be harder to look at
	for (int i = 0; i < 4; i++)
	{
		hitbox.setPoint(i, sf::Vector2f(hitbox.getPoint(i).x * WINDOW_SCALE, hitbox.getPoint(i).y * WINDOW_SCALE));

		switch (i) //switch is unnecessary but saves me from typing the enum 3 times on each case
		{
		case ConvexCorners::TOP_LEFT:
			hitbox.setPoint(i, sf::Vector2f(hitbox.getPoint(i).x - WINDOW_SCALE + WINDOW_SCALE,
				hitbox.getPoint(i).y - WINDOW_SCALE / 2.f));
			break;
		case ConvexCorners::TOP_RIGHT:
			hitbox.setPoint(i, sf::Vector2f(hitbox.getPoint(i).x + WINDOW_SCALE, 
				hitbox.getPoint(i).y - WINDOW_SCALE / 2.f));
			break;
		case ConvexCorners::BOT_LEFT:
			hitbox.setPoint(i, sf::Vector2f(hitbox.getPoint(i).x - WINDOW_SCALE + WINDOW_SCALE,
				hitbox.getPoint(i).y + WINDOW_SCALE / 2.f));
			break;
		case ConvexCorners::BOT_RIGHT:
			hitbox.setPoint(i, sf::Vector2f(hitbox.getPoint(i).x + WINDOW_SCALE,
				hitbox.getPoint(i).y + WINDOW_SCALE / 2.f));
			break;
		default: 
			break;
		}
	}

	img.loadFromFile(file);
	sprite.setTexture(img);
}


void Platform::drawTo(sf::RenderWindow& window) const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		window.draw(hitbox);
}

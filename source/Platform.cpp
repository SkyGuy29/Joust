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
	case PlatformNames::P_TOP_LEFT:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0, 62));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(28, 62));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(18, 68));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(0, 68));
		sprite.setAnimation(AnimationNames::PLAT_TOP_LEFT_ANIM);
		break;
	case PlatformNames::P_TOP_MIDDLE:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(80, 74));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(167, 74));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(125, 82));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(104, 82));
		sprite.setAnimation(AnimationNames::PLAT_TOP_CENTER_ANIM);
		break;
	case PlatformNames::P_TOP_RIGHT:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(246, 61));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(291, 61));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(291, 68));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(272, 68));
		sprite.setAnimation(AnimationNames::PLAT_TOP_RIGHT_ANIM);
		break;
	case PlatformNames::P_LEFT_SIDE:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(0, 131));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(59, 131));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(50, 138));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(14, 138));
		sprite.setAnimation(AnimationNames::PLAT_LEFT);
		break;
	case PlatformNames::P_BOTTOM_MIDDLE:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(100, 156));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(163, 156));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(139, 163));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(123, 163));
		sprite.setAnimation(AnimationNames::PLAT_CENTER_ANIM);
		break;
	case PlatformNames::P_RIGHT_SIDE:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(196, 122));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(253, 122));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(241, 132));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(223, 132));
		sprite.setAnimation(AnimationNames::PLAT_RIGHT);
		break;
	case PlatformNames::P_RIGHT_SIDE_SMALL:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(250, 131));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(291, 131));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(291, 137));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(255, 137));
		sprite.setAnimation(AnimationNames::PLAT_RIGHT_SMALL);
		break;
	case PlatformNames::P_GROUND:
		hitbox.setPoint(ConvexCorners::TOP_LEFT, sf::Vector2f(48, 204));
		hitbox.setPoint(ConvexCorners::TOP_RIGHT, sf::Vector2f(233, 204));
		hitbox.setPoint(ConvexCorners::BOT_RIGHT, sf::Vector2f(192, 236));
		hitbox.setPoint(ConvexCorners::BOT_LEFT, sf::Vector2f(74, 236));
		sprite.setAnimation(AnimationNames::PLAT_GROUND);
		break;
	}

	//offsetting hitboxes to fit the window scale and be positioned correctly
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

	sprite.setMode(Mode::END);

	sprite.setPos(sf::Vector2f((hitbox.getPoint(ConvexCorners::TOP_LEFT).x + hitbox.getPoint(ConvexCorners::TOP_RIGHT).x) / 2,
		(hitbox.getPoint(ConvexCorners::TOP_LEFT).y + hitbox.getPoint(ConvexCorners::BOT_LEFT).y) / 2));
}


void Platform::update()
{
	//sprite.nextFrame(10);
}

void Platform::drawTo(sf::RenderWindow& window) const
{
	sprite.drawTo(window);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		window.draw(hitbox);
}

#include "Collidable.h"


void Collidable::setOnGround(float newYValue, int platform)
{
	currentPlatform = platform;
	vel.y = 0;
	hitbox.setPosition(hitbox.getPosition().x, 
		newYValue - hitbox.getGlobalBounds().height - 0.1 + hitbox.getSize().y / 2.f);
}


void Collidable::bounceSetLeft(Platform platform)
{
	hitbox.setPosition((hitbox.getPosition().y - hitbox.getSize().y / 2.f - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		+ platform.getPointPos(ConvexCorners::TOP_LEFT).x - 50, hitbox.getPosition().y);
}


void Collidable::bounceSetRight(Platform platform)
{
	hitbox.setPosition((hitbox.getPosition().y - hitbox.getSize().y / 2.f - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x)
		/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x + 50, hitbox.getPosition().y);
}
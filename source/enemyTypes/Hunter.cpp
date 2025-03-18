#include "Hunter.h"


Hunter::Hunter()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(400, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::HUNTER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	vel.x = SPEED_INC_X;
}


void Hunter::update()
{
	Enemy::update();
}


void Hunter::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::HUNTER_GROUND);
	Enemy::setOnGround(newYValue, platform);
}

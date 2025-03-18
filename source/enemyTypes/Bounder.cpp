#include "Bounder.h"


Bounder::Bounder()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(500, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::BOUNDER_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	vel.x = SPEED_INC_X;
}


void Bounder::update()
{
	Enemy::update();
}


void Bounder::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::BOUNDER_GROUND);
	Enemy::setOnGround(newYValue, platform);
}

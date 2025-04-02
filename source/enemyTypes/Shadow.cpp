#include "Shadow.h"


Shadow::Shadow()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(300, 100);
	hitbox.setFillColor(sf::Color::Yellow);
	sprite.setAnimation(AnimationNames::SHADOW_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
	vel.x = SPEED_INC_X;
}


void Shadow::update(Player player[2])
{
	Enemy::update(player);

}


void Shadow::setOnGround(float newYValue, int platform)
{
	sprite.setAnimation(AnimationNames::SHADOW_GROUND);
	Enemy::setOnGround(newYValue, platform);
}
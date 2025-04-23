#include "Egg.h"


Egg::Egg()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition((rand() % 5 + 1)*100, 100);
	hitbox.setFillColor(sf::Color::Cyan);
	sprite.setAnimation(AnimationNames::EGG_FALL);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol

	eggTimer.restart();
}

Egg::Egg(sf::Vector2f startingPos, sf::Vector2f startingVel, EnemyTypes tempType)
{
	type = tempType;
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(startingPos);
	vel = startingVel;
	if (vel.y < 0)
		vel.y *= -.5;
	hitbox.setFillColor(sf::Color::Cyan);
	sprite.setAnimation(AnimationNames::EGG_FALL);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol

	eggTimer.restart();
}

void Egg::update()
{
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE));
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.move(vel);
	//uwu
	if (hitbox.getPosition().y - hitbox.getSize().y / 2.f < 0)
	{
		bounceY();
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x, (hitbox.getSize().y / 2.f)));
	}

	if (hitbox.getPosition().x < 0)
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x + WINDOW_X * WINDOW_SCALE,
			hitbox.getPosition().y));

	if (hitbox.getPosition().x > WINDOW_X * WINDOW_SCALE)
		hitbox.setPosition(sf::Vector2f(0, hitbox.getPosition().y));

	if (currentPlatform == -1 && sprite.getAnimation() != AnimationNames::EGG_HATCH)
		sprite.nextFrame(10);

	if (currentPlatform == -1)//gravity? who gives a crap about gravity?? ME!!
		vel.y += .125 * (WINDOW_SCALE / 3.f);
	else
		vel.x = 0;

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));

	if (getTimer() >= 15000)
		sprite.setAnimation(AnimationNames::EGG_HATCH);
}

void Egg::hatch()
{

}

void Egg::drawTo(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		window.draw(hitbox);
	sprite.drawTo(window);
}

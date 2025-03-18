#include "Egg.h"


Egg::Egg()
{
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(200, 100);
	hitbox.setFillColor(sf::Color::Cyan);
	sprite.setAnimation(AnimationNames::EGG_FALL);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
}

void Egg::update()
{
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE));
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.move(vel);

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

	if (currentPlatform == -1)
		sprite.nextFrame(10);

	if (currentPlatform == -1)//gravity? who gives a crap about gravity?? ME!!
	{
		vel.y += .125 * (WINDOW_SCALE / 3.f);
		//vel.x = 2 * (WINDOW_SCALE / 3.f);
	}


	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));
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

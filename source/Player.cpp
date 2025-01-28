#include "Player.h"


Player::Player()
{
	hitbox.setSize(sf::Vector2f(50, 50));
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(0, 550);
	hitbox.setFillColor(sf::Color::Green);
}


void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (vel.x > -12)
			vel.x -= 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (vel.x < 12)
		vel.x += 3;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && jumpKeyHeld == false)
	{
		jumpKeyHeld = true;
		vel.y -= 3.5;
	}

	vel.y += .5;

	hitbox.move(vel);


	//Checks if the jump key is held
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		jumpKeyHeld = false;
	}
}


void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
}
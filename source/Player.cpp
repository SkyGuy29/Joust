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
		vel.x = -3.125;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		vel.x = 3.125;
	}


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vel.x = 0;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vel.y = 0;
	}

	hitbox.move(vel);
}


void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
}
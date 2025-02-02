#include "Player.h"


Player::Player()
{
	hitbox.setSize(sf::Vector2f(50, 50));
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(0, 550);
	hitbox.setFillColor(sf::Color::Green);
	//sprite.setTexture("res/Art/joust sprites.png", sf::IntRect())
}


void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (vel.x > -6)
			vel.x -= 1.5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (vel.x < 6)
		vel.x += 1.5;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && jumpKeyHeld == false)
	{
		jumpKeyHeld = true;
		vel.y -= 2;
	}

	vel.y += .125;

	hitbox.move(vel);


	//Checks if the jump key is held
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		jumpKeyHeld = false;
	}
}

sf::RectangleShape Player::getHitbox()
{
	return hitbox;
}


void Player::drawTo(sf::RenderWindow& window)
{
	//sprite.drawTo(window);
	window.draw(hitbox);
}
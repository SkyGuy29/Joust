#include "Player.h"


Player::Player()
{
	hitbox.setSize(sf::Vector2f(50, 50));
	//TODO:
	// - change origin to center
	// - set sprite to hitbox position instead of the offset
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(0, 550);
	hitbox.setFillColor(sf::Color::Green);
	//sprite.setTexture("res/art/joustSprite.png", sf::IntRect(247, 64, 15, 18), 4); //running
	sprite.setTexture("res/art/joustSprite.png", sf::IntRect(247, 102, 15, 12), 2);
}


void Player::update()
{
	hitbox.move(vel);

	//Checks if the jump key is held
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		jumpKeyHeld = false;
	}

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

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2));

	sprite.nextFrame();
}


sf::RectangleShape Player::getHitbox()
{
	return hitbox;
}


sf::Vector2f Player::getVelocity()
{
	return vel;
}


void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
	sprite.drawTo(window);
}
#include "Player.h"


Player::Player()
{
	hitbox.setSize(sf::Vector2f(54, 54)); //not exact lol
	//TODO:
	// - change origin to center
	// - set sprite to hitbox position instead of the offset
	hitbox.setOrigin(0, 0);
	hitbox.setPosition(0, 550);
	hitbox.setFillColor(sf::Color::Green);
	sprite.setImage("res/art/joustSprite.png");
	sprite.setAnimation(DataNames::P1_GROUND);
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
		//sprite.setFrame(0); //flapping, wings up
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

	if (!jumpKeyHeld && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
	{
		jumpKeyHeld = true;
		//sprite.setFrame(1); //flapping, wings down
		sprite.nextFrame();
		vel.y -= 2;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			vel.y = 1.5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			hitbox.setPosition(100, 100);
			vel.y = 0;
			vel.x = 0;
		}
	}
	else
		vel.y += .125;

	//sprite.nextFrame();
	sprite.setPos(sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2, hitbox.getPosition().y + hitbox.getSize().y / 2));
}


sf::FloatRect Player::getHitbox()
{
	return hitbox.getGlobalBounds();
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
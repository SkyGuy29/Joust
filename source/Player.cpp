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
	sprite.setAnimation(AnimationNames::P1_GROUND);
}


void Player::update()
{
	hitbox.move(vel);

	//Checks if the jump key is held
	if (!isJumpPressed())
	{
		jumpKeyHeld = false;
		//sprite.setFrame(0); //flapping, wings up
	}

	if (onGround) 
	{
		if (isLeftPressed())
		{
			if (vel.x > -6)
				vel.x -= 1.5;
		}
		if (isRightPressed())
		{
			if (vel.x < 6)
				vel.x += 1.5;
		}
	}

	if (!jumpKeyHeld && isJumpPressed())
	{
		jumpKeyHeld = true;
		//sprite.setFrame(1); //flapping, wings down
		sprite.nextFrame();
		vel.y -= 2;

		if (!onGround)
		{
			if (isLeftPressed())
			{
				if (vel.x > -6)
					vel.x -= 1.5;
			}
			else if (isRightPressed())
			{
				if (vel.x < 6)
					vel.x += 1.5;
			}
		}
		else
			onGround = false;
	}

	//debug keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (isDownPressed())
			vel.y = 1.5;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			hitbox.setPosition(100, 100);
			vel.y = 0;
			vel.x = 0;
		}
	}
	else if (!onGround) //gravity
		vel.y += .125;

	if (vel.x > 0)
		sprite.faceRight(true);
	else if (vel.x < 0)
		sprite.faceRight(false);

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2,
		hitbox.getPosition().y + hitbox.getSize().y / 2));
}


void Player::setOnGround(float newYValue)
{
	onGround = true;

	vel.y = 0;
	hitbox.setPosition(hitbox.getPosition().x, newYValue - hitbox.getGlobalBounds().height - 0.1);
	sprite.setAnimation(AnimationNames::P1_GROUND);
	sprite.setPos(sf::Vector2f(hitbox.getPosition().x + hitbox.getSize().x / 2,
		hitbox.getPosition().y + hitbox.getSize().y / 2));

}

void Player::drawTo(sf::RenderWindow& window)
{
	window.draw(hitbox);
	sprite.drawTo(window);
}


bool Player::isLeftPressed()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}


bool Player::isRightPressed() 
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}


bool Player::isDownPressed()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
}


bool Player::isJumpPressed()
{
	return !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}
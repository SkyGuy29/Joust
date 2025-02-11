#include "Player.h"


Player::Player()
{
	hitbox.setSize(sf::Vector2f(54, 54)); //not exact lol
	//TODO:
	// - change origin to center
	// - set sprite to hitbox position instead of the offset
	hitbox.setOrigin(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
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
		if(!onGround)
			sprite.setFrame(0); //flapping, wings up
	}

	if (onGround || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
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
		vel.y -= 2;

		if (!onGround)
		{
			sprite.setFrame(1); //flapping, wings down

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

	
	if (onGround)
		sprite.nextFrame();

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));
}


void Player::setOnGround(float newYValue)
{
	onGround = true;

	vel.y = 0;
	hitbox.setPosition(hitbox.getPosition().x, newYValue - hitbox.getGlobalBounds().height - 0.1 + hitbox.getSize().y / 2.f);
	sprite.setAnimation(AnimationNames::P1_GROUND);
	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));

}


void Player::setPosition(sf::Vector2f newPos)
{
	hitbox.setPosition(newPos);
}


void Player::bounceSetLeft(Platform platform)
{
	hitbox.setPosition((((hitbox.getPosition().x) - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
		/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x, hitbox.getPosition().y);
}


void Player::bounceSetRight(Platform platform)
{
	hitbox.setPosition((((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
		/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x, hitbox.getPosition().y);
}


void Player::bounceX()
{
	vel.x *= -1;
}


void Player::bounceY()
{
	vel.y *= -1;
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
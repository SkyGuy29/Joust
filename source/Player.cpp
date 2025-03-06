#include "Player.h"


Player::Player()
{
	//TODO:
	// - change origin to center
	// - set sprite to hitbox position instead of the offset
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(100, 100);
	hitbox.setFillColor(sf::Color::Green);
	sprite.setImage("res/art/joustSprite.png");
	sprite.setAnimation(AnimationNames::P1_FLY);
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE)); //not exact lol
}


void Player::update()
{
	hitbox.setSize(sf::Vector2f(sprite.getBounds().width * WINDOW_SCALE, sprite.getBounds().height * WINDOW_SCALE));
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.move(vel);

	//Checks if the jump key is held
	if (!isJumpPressed())
	{
		jumpKeyHeld = false;
		if (!onGround)
			sprite.setFrame(0); //flapping, wings up
	}

	if (onGround || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (isLeftPressed())
		{
			if (leftTimer >= 8)
			{
				if (vel.x > -SPEED_MAX_X)
					vel.x -= SPEED_INC_X;
				sprite.setFaceRight(false);
				leftTimer = 0;
			}
			else leftTimer++;
		}
		if (isRightPressed())
		{
			if (rightTimer >= 8)
			{
				if (vel.x < SPEED_MAX_X)
					vel.x += SPEED_INC_X;
				sprite.setFaceRight(true);
				rightTimer = 0;
			}
			else rightTimer++;
		}
	}

	if (!jumpKeyHeld && isJumpPressed())
	{
		jumpKeyHeld = true;
		vel.y -= 2 * (WINDOW_SCALE / 3.f);

		if (!onGround)
		{
			sprite.setFrame(1); //flapping, wings down

			if (isLeftPressed())
			{
	
					if (vel.x > -SPEED_MAX_X)
						vel.x -= SPEED_INC_X;
					sprite.setFaceRight(false);
			}
			else if (isRightPressed())
			{

					if (vel.x < SPEED_MAX_X)
						vel.x += SPEED_INC_X;
					sprite.setFaceRight(true);
			}
		}
		else
			setOffGround();
	}

	//debug keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if (isDownPressed())
			vel.y = SPEED_INC_X;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
		{
			hitbox.setPosition(100, 100);
			vel.y = 0;
			vel.x = 0;
		}
	}
	else if (!onGround) //gravity
		vel.y += .125 * (WINDOW_SCALE / 3.f);

	//formerly "isTouchingBounds()" from Game, moving to here made more sense
	if (hitbox.getPosition().y - hitbox.getSize().y / 2.f < 0)
		bounceY();

	if (hitbox.getPosition().x < 0)
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x + WINDOW_X * WINDOW_SCALE,
			hitbox.getPosition().y));

	if (hitbox.getPosition().x > WINDOW_X * WINDOW_SCALE)
		hitbox.setPosition(sf::Vector2f(0, hitbox.getPosition().y));

	speed = vel.x / SPEED_INC_X;
	if (speed < 0)
		speed *= -1;

	if (onGround && frameCounter + speed * 2 >= 10)
	{
		sprite.nextFrame();
		frameCounter = 0;
		if (speed == 0)
			sprite.setFrame(3);
	}
	else
		frameCounter++;
	//if (onGround)
		//sprite.nextFrame();

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));
}


void Player::setOnGround(float newYValue)
{
	Collidable::setOnGround(newYValue);
	sprite.setAnimation(AnimationNames::P1_GROUND);
	sprite.setPos(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y));
	sprite.setFaceRight(vel.x > 0);
}


void Player::setPosition(sf::Vector2f newPos)
{
	hitbox.setPosition(newPos);
}


void Player::bounceSetLeft(Platform platform)
{
	hitbox.setPosition(((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_LEFT).y) 
		* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		+ platform.getPointPos(ConvexCorners::TOP_LEFT).x - 50, hitbox.getPosition().y);
}


void Player::bounceSetRight(Platform platform)
{
	hitbox.setPosition((((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		* (platform.getPointPos(ConvexCorners::BOT_RIGHT).x - platform.getPointPos(ConvexCorners::TOP_RIGHT).x))
		/ (platform.getPointPos(ConvexCorners::BOT_RIGHT).y - platform.getPointPos(ConvexCorners::TOP_RIGHT).y)
		+ platform.getPointPos(ConvexCorners::TOP_RIGHT).x + 50, hitbox.getPosition().y);
}


void Player::drawTo(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
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
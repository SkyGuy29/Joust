#include "Player.h"


Player::Player()
{
	//TODO:
	// - change origin to center -- done?
	// - set sprite to hitbox position instead of the offset
	hitbox.setOrigin(hitbox.getSize().x / 2.f, hitbox.getSize().y / 2.f);
	hitbox.setPosition(5000, 5000);
	hitbox.setFillColor(sf::Color::Green);
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
		if (currentPlatform == -1)
			sprite.setFrame(0); //flapping, wings up
	}

	//velocity increase and skidding
	if ((currentPlatform >= 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) && disable == false)
	{
		if (isLeftPressed() || (skid == true && vel.x > 0))
		{
			if (leftTimer >= 8)
			{
				sprite.setFaceRight(false);
				if (vel.x > -SPEED_MAX_X)
					vel.x -= SPEED_INC_X;
				if (vel.x >= SPEED_INC_X * 2)
				{
					skid = true;
					sprite.setAnimation(P1_SKID);
				}
				leftTimer = 0;
			}
			else leftTimer++;
		}
		if (isRightPressed() || (skid == true && vel.x < 0))
		{
			if (rightTimer >= 8)
			{
				sprite.setFaceRight(true);
				if (vel.x < SPEED_MAX_X)
					vel.x += SPEED_INC_X;
				if (vel.x <= -SPEED_INC_X * 2)
				{
					skid = true;
					sprite.setAnimation(P1_SKID);
				}
				rightTimer = 0;
			}
			else rightTimer++;
		}
	}
	//skid logic
	if (skid == true && vel.x == 0 && currentPlatform >= 0)
	{
		skid = false;
		sprite.setAnimation(AnimationNames::P1_GROUND);
	}
	
	//flight
	if (!jumpKeyHeld && isJumpPressed() && disable == false)
	{
		jumpKeyHeld = true;
		vel.y -= 2 * (WINDOW_SCALE / 3.f);

		if (currentPlatform == -1)
		{
			sprite.setFrame(1); //flapping, wings down

			if (isLeftPressed())
			{
				sprite.setFaceRight(false);
				if (vel.x > -SPEED_MAX_X)
					vel.x -= SPEED_INC_X;
			}
			else if (isRightPressed())
			{
				sprite.setFaceRight(true);
				if (vel.x < SPEED_MAX_X)
					vel.x += SPEED_INC_X;
			}
		}
		else
			setOffGround();
	}

	//debug keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && disable == false)
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
	else if (currentPlatform == -1 && gravity == true) //gravity
		vel.y += .125 * (WINDOW_SCALE / 3.f);

	//next three ifs were formerly "isTouchingBounds()" from Game, moving to here made more sense
	//these three ifs detail interactions with the boundaries of the screen
	//top boundary
	if (hitbox.getPosition().y - hitbox.getSize().y / 2.f < 0)
	{
		bounceY();
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x, (hitbox.getSize().y / 2.f)));
	}

	//left side tp
	if (hitbox.getPosition().x < 0)
	{
		hitbox.setPosition(sf::Vector2f(hitbox.getPosition().x + WINDOW_X * WINDOW_SCALE,
			hitbox.getPosition().y));
		if (currentPlatform == P_TOP_LEFT)
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_TOP_RIGHT);
		else if (currentPlatform == P_LEFT_SIDE)
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_RIGHT_SIDE_SMALL);
	}

	//right side tp
	if (hitbox.getPosition().x > WINDOW_X * WINDOW_SCALE)
	{
		hitbox.setPosition(sf::Vector2f(0, hitbox.getPosition().y));

		if (currentPlatform == P_TOP_RIGHT)
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_TOP_LEFT);
		else if (currentPlatform == P_RIGHT_SIDE_SMALL)
			setOnGround(hitbox.getPosition().y + hitbox.getSize().y / 2.f, P_LEFT_SIDE);
	}

	//player run animation based on speed
	speed = abs(vel.x) / SPEED_INC_X;
	
	if (currentPlatform >= 0 && frameCounter + speed * 2 >= 10)
	{
		sprite.nextFrame();
		frameCounter = 0;
		if (speed == 0)
			sprite.setFrame(3);
	}
	else
		frameCounter++;

	//set the sprite to the hitbox location
	sprite.setPos(sf::Vector2f(hitbox.getPosition().x,
		hitbox.getPosition().y));
}


//sets the player on the ground
void Player::setOnGround(float newYValue, int platform)
{
	Collidable::setOnGround(newYValue, platform);
	if (skid == false)
		sprite.setAnimation(AnimationNames::P1_GROUND);
	else
		sprite.setAnimation(AnimationNames::P1_SKID);

	sprite.setPos(sf::Vector2f(hitbox.getPosition().x, hitbox.getPosition().y));
	sprite.setFaceRight(vel.x > 0);
#ifdef DEBUG
	std::cout << "Player\n";
#endif
}


void Player::setPosition(sf::Vector2f newPos)
{
	hitbox.setPosition(newPos);
}


//sets the player to where they bounce off, this stops infinite collisions and glitching into platforms
void Player::bounceSetLeft(Platform& platform)
{
	hitbox.setPosition(((hitbox.getPosition().y - hitbox.getSize().y / 2.f) - platform.getPointPos(ConvexCorners::TOP_LEFT).y) 
		* (platform.getPointPos(ConvexCorners::BOT_LEFT).x - platform.getPointPos(ConvexCorners::TOP_LEFT).x)
		/ (platform.getPointPos(ConvexCorners::BOT_LEFT).y - platform.getPointPos(ConvexCorners::TOP_LEFT).y)
		+ platform.getPointPos(ConvexCorners::TOP_LEFT).x - 50, hitbox.getPosition().y);
}


void Player::bounceSetRight(Platform& platform)
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


void Player::toggleGravity(bool temp)
{
	gravity = temp;
}


void Player::toggleDisable(bool temp)
{
	disable = temp;
}


void Player::setRespawn()
{
	// respawn animation
	sprite.setAnimation(AnimationNames::P1_SPAWN);

	//example rand spawn
	switch (rand() % 4)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		hitbox.setPosition(100, 100);
		break;
	}

	// set player to spawn point



	// outside: set enemies to no target

	// outside reduce lives


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
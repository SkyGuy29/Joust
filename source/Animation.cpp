#include "Animation.h"


Animation::Animation()
{
	sprite.setScale(sf::Vector2f(WINDOW_SCALE, WINDOW_SCALE));
}


void Animation::setAnimation(const AnimationNames data)
{
	if (data != currentAnimation)
	{
		if (spriteData[data].fileName != spriteData[currentAnimation].fileName)
		{
			image.loadFromFile(spriteData[data].fileName);
			sprite.setTexture(image);
		}
		currentAnimation = data;
		reset();
		//centers the sprite for use with setPosition
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		maxFrame = spriteData[data].frameCount;
		delayCount = 0;
	}
}


void Animation::setFaceRight(const bool right)
{
	if (facingRight != right)
	{
		facingRight = right;
		sprite.setScale(-sprite.getScale().x, sprite.getScale().y);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}
}


void Animation::nextFrame(int delay)
{
	if (++delayCount % delay == 0) //this will trigger once every (delay) frames
	{
		delayCount = 0;
		sf::IntRect spriteRect = sprite.getTextureRect();

		if (currentFrame++ < maxFrame - 1) //if not out of bounds...
			spriteRect.left += spriteRect.width;
		else if (currentMode == Mode::END) //if set to end, do nothing
			currentFrame = maxFrame - 1;
		else if (currentMode == Mode::LOOP) //if set to loop, reset the counter and rect
		{
			currentFrame = 0;
			spriteRect = spriteData[currentAnimation].bounds;
		}
		else if (currentMode == Mode::REVERSE) //if set to reverse, go backwards (untested)
		{
			currentFrame = 0;
			spriteRect.left -= spriteRect.width * (maxFrame - 1);
		}

		sprite.setTextureRect(spriteRect);
	}
}


bool Animation::nextSpawnFrame(int delay)
{
	sf::IntRect spriteRect = sprite.getTextureRect();

	switch (currentAnimation)
	{
		case AnimationNames::P1_SPAWN:
		case AnimationNames::P2_SPAWN:
		case AnimationNames::ENEMY_SPAWN:
			if (++delayCount % delay == 0) //frame counter
			{
				delayCount = 0;

				if (!spawnFirstLoop && spriteRect.height == spriteData[currentAnimation].bounds.height)
				{
					spawnFirstLoop = true; //reset it for next spawn
					return true; //once the first loop is done, return true
				}

				spriteRect.height++; //move it down
				sprite.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y + 1);
			}

			if (spawnFirstLoop && spriteRect.height == spriteData[currentAnimation].bounds.height) //placed outside so that it can trigger before the first draw
			{
				spawnFirstLoop = false; //this is the first loop, so don't return true yet
				spriteRect.height = 0; //move it up to start the spawning
				sprite.setOrigin(sprite.getOrigin().x, sprite.getOrigin().y - spriteData[currentAnimation].bounds.height);
			}

			sprite.setTextureRect(spriteRect);
			return false;
		default:
			return true; //only the listed animations are allowed to spawn
	}
}


void Animation::setFrame(const int newFrame)
{
	sf::IntRect spriteRect = sprite.getTextureRect();
	const int frameDiff = newFrame - currentFrame;
	currentFrame = newFrame;
	spriteRect.left += spriteRect.width * frameDiff;
	sprite.setTextureRect(spriteRect);
}


void Animation::drawTo(sf::RenderWindow& window) const
{
	switch (currentAnimation)
	{
	case AnimationNames::P1_SPAWN:
	case AnimationNames::P2_SPAWN:
	case AnimationNames::ENEMY_SPAWN:
		if (spawnFirstLoop)
			break;
	default:
		window.draw(sprite);
	}
}
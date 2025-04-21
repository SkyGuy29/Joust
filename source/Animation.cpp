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
	if(++delayCount % delay == 0)
	{
		delayCount = 0;
		sf::IntRect spriteRect = sprite.getTextureRect();

		if (currentFrame++ < maxFrame - 1) //if not out of bounds...
		{
			spriteRect.left += spriteRect.width;
		}
		else if (currentMode == Mode::END) //if set to end, do nothing
		{
			currentFrame = maxFrame - 1;
		}
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


void Animation::nextSpawnFrame(int delay)
{
	if (++delayCount % delay == 0)
	{
		delayCount = 0;
		sf::IntRect spriteRect = sprite.getTextureRect();

		if (spriteRect == spriteData[currentAnimation].bounds) //if they are still equal...
		{
			spriteRect.top -= spriteRect.height; //move it up to start the spawning
		}

		if (spriteRect.top != spriteData[currentAnimation].bounds.top) //if not at the bottom...
		{
			spriteRect.top++; //move it down
		}

		sprite.setTextureRect(spriteRect);
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
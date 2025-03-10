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


void Animation::nextFrame()
{
	sf::IntRect spriteRect = sprite.getTextureRect();

	if (currentFrame++ < maxFrame - 1) //if not out of bounds...
	{
		spriteRect.left += spriteRect.width;
	}
	else if (currentMode == Mode::LOOP) //if set to loop, reset the counter and rect
	{
		currentFrame = 0;
		spriteRect = spriteData[currentAnimation].bounds;
	}

	sprite.setTextureRect(spriteRect);
}


void Animation::setFrame(const int newFrame)
{
	sf::IntRect spriteRect = sprite.getTextureRect();
	const int frameDiff = newFrame - currentFrame;
	currentFrame = newFrame;
	spriteRect.left += spriteRect.width * frameDiff;
	sprite.setTextureRect(spriteRect);
}

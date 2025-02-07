#include "Animation.h"


Animation::Animation()
{
	sprite.setScale(sf::Vector2f(WINDOW_SCALE, WINDOW_SCALE));
}


void Animation::setImage(std::string fileName)
{
	image.loadFromFile(fileName);
	sprite.setTexture(image);
}


void Animation::setAnimation(AnimationNames data)
{
	currentAnimation = data;
	sprite.setTextureRect(spriteData[data].bounds);
	sprite.setScale(sf::Vector2f(WINDOW_SCALE, WINDOW_SCALE));
	//centers the sprite for use with setPosition
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	maxFrame = spriteData[data].frameCount;
}


void Animation::nextFrame()
{
	sf::IntRect spriteRect = sprite.getTextureRect();

	if (currentFrame++ < (maxFrame - 1)) //if not out of bounds...
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


void Animation::setFrame(int newFrame)
{
	sf::IntRect spriteRect = sprite.getTextureRect();
	int frameDiff = newFrame - currentFrame;
	currentFrame = newFrame;
	spriteRect.left += spriteRect.width * frameDiff;
	sprite.setTextureRect(spriteRect);
}

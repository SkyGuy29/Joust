#include "Animation.h"


void Animation::setTexture(std::string fileName, sf::IntRect spriteRect, int maxFrames)
{
	image.loadFromFile(fileName);
	sprite.setTexture(image);
	sprite.setTextureRect(spriteRect);
	sprite.setScale(sf::Vector2f(WINDOW_SCALE, WINDOW_SCALE));
	//centers the sprite for use with setPosition
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	maxFrameCount = maxFrames;
}


void Animation::nextFrame()
{
	sf::IntRect spriteRect = sprite.getTextureRect();

	if (currentFrameCount++ < maxFrameCount) //won't increase if they are equal
	{
		spriteRect.left += spriteRect.width;
		sprite.setTextureRect(spriteRect);
	}
	else if (currentMode == Mode::LOOP)
	{
		currentFrameCount = 1;
		spriteRect.left -= spriteRect.width * (maxFrameCount - 1);

		sprite.setTextureRect(spriteRect);
	}
}


void Animation::setFrame(int newFrameCount)
{
	if (currentFrameCount > 0 && currentFrameCount <= maxFrameCount)
	{
		sf::IntRect spriteRect = sprite.getTextureRect();
		int frameDiff = newFrameCount - currentFrameCount;

		currentFrameCount = newFrameCount;
		spriteRect.left += spriteRect.width * frameDiff;
		sprite.setTextureRect(spriteRect);
	}
}

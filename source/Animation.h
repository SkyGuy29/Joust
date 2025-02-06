#pragma once
#include "globals.hpp"


enum class Mode
{
	END, //if the frame counter is on the last frame, don't increase.
	LOOP, //if the frame counter is on the last frame, go to the first one.
	REVERSE //if the frame counter is on the last frame, start counting down.
};


//Easy api to handle animated sprites. Only works with spritesheets.
class Animation
{
public:
	Animation();

	//sets the texture of the animation with a filename. Must be called before setting the animation.
	void setImage(std::string);
	
	//changes which animation you are using, allows for quick swapping within an image.
	void setAnimation(AnimationNames);

	//gets the name of the sprite's current animation.
	AnimationNames getAnimation() const { return currentAnimation; }

	//resets the animation. that should be obvious.
	void reset() { currentFrame = 0; sprite.setTextureRect(spriteData[currentAnimation].bounds); }

	//sets the end behavior of an animation.
	void setMode(Mode newMode) { currentMode = newMode; }

	//sets the position of the animation like any other SFML drawable
	void setPos(sf::Vector2f pos) { sprite.setPosition(pos); }

	//moves the frameCounter to the next frame
	//GUESS WHO'S BACK =D
	void nextFrame();

	//sets the animation to a given frame.
	//does nothing if you try to set the frame past the max.
	void setFrame(int newFrameCount);

	//draws the animation to the passed in window.
	void drawTo(sf::RenderWindow& window) { window.draw(sprite); }
private:
	sf::Texture image;
	sf::Sprite sprite;
	int maxFrame = 5, //this is how many sprites there are in the animation 
		currentFrame = 0; //THE FIRST FRAME IS 0 LIKE AN ARRAY
	Mode currentMode = Mode::LOOP;
	AnimationNames currentAnimation = AnimationNames::DATA_COUNT;
};
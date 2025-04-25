#pragma once
#include "SpriteData.h"


enum class Mode
{
	END, //if the frame counter is on the last frame, don't increase.
	LOOP, //if the frame counter is on the last frame, go to the first one.
	REVERSE //if the frame counter is on the last frame, start counting down.
};


//Easy api to handle animated sprites. Only works with sprite sheets.
//With how this is set up, animations must be done horizontally and must be spaced evenly.
class Animation
{
public:
	Animation();
	
	//changes and which animation you are using, allows for quick swapping.
	//this does reset the animation. if you need it to start at a particular spot you will
	//need to set it again.
	void setAnimation(AnimationNames);

	//gets the name of the sprite's current animation.
	AnimationNames getAnimation() const { return currentAnimation; }

	//returns the box for the animation sprite.
	sf::IntRect getBounds() const { return spriteData[currentAnimation].bounds; }

	//resets the animation. that should be obvious.
	void reset() { currentFrame = 0; sprite.setTextureRect(spriteData[currentAnimation].bounds); }

	//sets the end behavior of an animation.
	void setMode(const Mode newMode) { currentMode = newMode; }

	//sets the position of the animation like any other SFML drawable
	void setPos(const sf::Vector2f pos) { sprite.setPosition(pos); }

	//makes the sprite face right or left depending on the bool you put in it
	void setFaceRight(bool);
	bool getFaceRight() const { return facingRight; }

	//moves the frameCounter to the next frame
	//optional delay parameter slows down frame changes,
	//every (delay) frames it advances the animation.
	//default value is 1, advances every frame
	void nextFrame(int = 1);

	//moves the texture rect down to replicate spawning.
	//does not change which frame is being displayed.
	//returns true if spawn animation is finished, false if not.
	bool nextSpawnFrame(int = 1);

	//sets the animation to a given frame.
	//you are fully allowed to set this past the max. 
	//The max is simply there for looping or other ends.
	void setFrame(int);
	int getFrame() const { return currentFrame; }

	//draws the animation to the passed in window.
	void drawTo(sf::RenderWindow& window) const { window.draw(sprite); }
private:
	sf::Texture image;
	sf::Sprite sprite;
	int maxFrame = 5, //this is how many sprites there are in the animation 
		currentFrame = 0, //THE FIRST FRAME IS 0 LIKE AN ARRAY
		delayCount = 0;  
	bool facingRight = true;
	bool spawnFirstLoop = true; //used to make the spawn animation only cycle once before returning
	Mode currentMode = Mode::LOOP;
	AnimationNames currentAnimation = AnimationNames::DATA_COUNT;
};
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
	//sets the texture of the animation and initializes a bunch of stuff.
	//the IntRect can be made something like this:
	//sf::IntRect(topLeftCorner (Vector2f), size (Vector2f))
	void setImage(std::string);
	void setAnimation(DataNames);
	void setMode(Mode newMode) { currentMode = newMode; }
	void setPos(sf::Vector2f pos) { sprite.setPosition(pos); }
	//moves the frameCounter to the next frame
	//GUESS WHO'S BACK =D
	void nextFrame();
	
	//sets the animation to a certain frame.
	//does nothing if you try to set the frame past the max.
	void setFrame(int newFrameCount);
	void drawTo(sf::RenderWindow& window) { window.draw(sprite); }
private:
	sf::Texture image;
	sf::Sprite sprite;
	int maxFrame = 5, //this is how many sprites there are in the animation 
		currentFrame = 0; //THE FIRST FRAME IS 0 LIKE AN ARRAY
	Mode currentMode = Mode::LOOP;
	DataNames currentAnimation;
};
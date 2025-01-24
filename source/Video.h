#pragma once
#include <SFML/Graphics.hpp>


/// <summary>
/// holds the data needed for a video cutscene (ones with complex animations that we could not recreate) and provides tools to handle said cutscenes.
/// really the difficulty of this is 
/// </summary>
class Video
{
public:
	//draws the VideoCutscene to the passed in RenderWindow
	//returns false when the cutscene is over
	bool drawTo(sf::RenderWindow&);

	//sets the video back to the beginning.
	void resetVideo() { index = 0; }
private:
	unsigned short index = 0; //current frame number
	int lastFrame = 0;
	sf::Texture image;
	sf::Sprite frame;

	//loads the current frame
	void loadFrame();
};


#include "Video.h"
#include <iostream>


bool Video::drawTo(sf::RenderWindow& window)
{
	loadFrame();
	window.draw(frame);
	return index < lastFrame;
}


void Video::loadFrame()
{
	//while (!image.loadFromFile("res/POUQGWFBHYGOIAVSC_PLACEHOLDER" + std::to_string(index++) + ".png")) {}
	frame.setTexture(image);
}

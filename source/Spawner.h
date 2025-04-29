#pragma once
#include "globals.hpp"
#include "Animation.h"

//class strictly to manage positioning and drawing of the spawners on the platforms.
//when a player or enemy spawns, one of the four spawners will have it rise out of the ground.
//part of this is that the spawner on the platform changes colors based on which is rising.
class Spawner
{
public:
	Spawner() = default;
	~Spawner() = default;

	//sets the spawner's position to its corresponding platform. if that platform has no spawner, ignore it
	void setPlatform(PlatformNames);

	//sets the spawner's animation to the passed in animation.
	//ignores invalid options.
	void setSpawnAnim(AnimationNames);

	//updates the platform's animation.
	void update() { sprite.nextFrame(10); }

	//draws the platform to the passed in window.
	void drawTo(sf::RenderWindow& window) { sprite.drawTo(window); }
private:
	Animation sprite;
};


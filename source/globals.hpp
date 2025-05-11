#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>


static constexpr auto PI = 3.1415926535897932;
static constexpr int WINDOW_SCALE = 3;
static constexpr int WINDOW_X = 292; //old (SNES) is 236
static constexpr int WINDOW_Y = 240; //old (SNES)is 194
static constexpr float SPEED_INC_X = .5 * WINDOW_SCALE;
static constexpr float SPEED_MAX_X = 2 * WINDOW_SCALE;
static constexpr int FPS = 60;


//returns the distance between two points.
static float distBetween(const sf::Vector2f point1, const sf::Vector2f point2)
{
    const sf::Vector2f d = point1 - point2;
    return hypotf(d.x, d.y);
}


//enum used for convex shapes.
//makes it easier to choose the point.
enum ConvexCorners 
{
    TOP_LEFT = 0,
    TOP_RIGHT,
    BOT_RIGHT,
    BOT_LEFT
};


//enum for type of collision with a platform.
enum class PlatformCollisionType
{
    TOP,
    BOT,
    LEFT,
    LEFT_HIGH,
    RIGHT,
    RIGHT_HIGH,
    NONE
};


//enum for the names of each platform
enum PlatformNames
{
	P_TOP_MIDDLE = 0,
    P_RIGHT_SIDE,
    P_RIGHT_SIDE_SMALL,
    P_LEFT_SIDE,
	P_BOTTOM_MIDDLE,
	P_TOP_LEFT,
	P_TOP_RIGHT,
	P_GROUND,
    PLATFORM_COUNT
};


enum EnemyTypes
{
    EMPTY = 0,
    BOUNDER,
    HUNTER,
    SHADOW
};
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


static constexpr auto PI = 3.1415926535897932;
static constexpr int WINDOW_SCALE = 6;
static constexpr int WINDOW_X = 292;
static constexpr int WINDOW_Y = 240;
static constexpr float SPEED_INC_X = .5 * WINDOW_SCALE;
static constexpr float SPEED_MAX_X = 2 * WINDOW_SCALE;
static constexpr int FPS = 60;


//returns the distance between two points.
static float distBetween(const sf::Vector2f point1, const sf::Vector2f point2)
{
    const sf::Vector2f d = point1 - point2;
    return hypotf(d.x, d.y);
}


//uses the law of cosines to create an angle given three points.
//the three points are used to create a triangle, and it finds an angle in that triangle.
//the angle returned is the one that corresponds to the first parameter/point here.
//the order of the last two does not matter.
static float lawOfCos(const sf::Vector2f p1, const sf::Vector2f p2, const sf::Vector2f p3)
{
    double a, b, c;
    a = distBetween(p1, p2);
    b = distBetween(p1, p3);
    c = distBetween(p2, p3);

    //the law in states that (the angle opposite of c) = acos((a*a + b*b - c*c) / (2ab))
    return acos((a * a + c * c - b * b) / (2 * a * c));
}
//aaaaand we didnt even use it LOL


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

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


static constexpr auto PI = 3.1415926535897932;
static constexpr int WINDOW_SCALE = 3;
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
    RIGHT
};


//simple data class for use with the spriteData array.
struct SpriteData
{
    SpriteData(sf::IntRect a, int b) { bounds = a; frameCount = b; }
    sf::IntRect bounds;
    int frameCount;
};


//names for the data you want.
enum AnimationNames
{
    P1_GROUND,
    P1_SKID,
    P1_FLY,
    P1_BIRD_GROUND,
    P1_BIRD_FLY,
    DEATH,
    EGG_FALL,
    DATA_COUNT //this helps make sure array size matches enum count
};


//container for all of the sprite data. please use the DataNames enum with this.
static const SpriteData spriteData[AnimationNames::DATA_COUNT] = 
{
    //all of the data follows this pattern:
    //(startPixelX, startPixelY, spriteWidth, spriteHeight), frameCount
    {sf::IntRect(247, 64, 15, 18), 4},  //P1_GROUND
    {sf::IntRect(248, 84, 13, 16), 1},  //P1_SKID
    {sf::IntRect(247, 102, 15, 12), 2}, //P1_FLY
    {sf::IntRect(248, 136, 13, 18), 4}, //P1_BIRD_GROUND
    {sf::IntRect(247, 156, 15, 12), 2}, //P1_BIRD_FLY
    {sf::IntRect(247, 173, 13, 13), 3}, //DEATH
    {sf::IntRect(248, 286, 7, 6), 3}    //EGG_FALL
};

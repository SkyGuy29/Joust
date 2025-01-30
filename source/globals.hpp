#pragma once

/*
Adressing global constants now:

I like making a file specifically for global stuff.
In basically any header file, put include this file and it will get all of the includes we need,
all of the global constants we use, any macros we set up, any very useful functions, etc.
Maybe it's not the best practice but it is clean and simple so I love it.
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//I use this sometimes but we don't need to use it
//#define isKeyPressed sf::Keyboard::isKeyPressed

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

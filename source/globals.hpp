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

//I use this sometimes but we don't need to use it
//#define isKeyPressed sf::Keyboard::isKeyPressed

const static int windowScaleFactor = 3;

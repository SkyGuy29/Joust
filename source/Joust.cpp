#include "Joust.h"


Joust::Joust()
{
    const int windowMult = 3; //we will adress global consts later for now im putting this here
    window.create(sf::VideoMode(240 * windowMult, 292 * windowMult), "Joust");

    window.setFramerateLimit(30);
}


void Joust::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        game.update();

        window.clear();

        game.drawTo(window);

        window.display();
    }
}

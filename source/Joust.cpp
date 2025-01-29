#include "Joust.h"


Joust::Joust()
{
    window.create(sf::VideoMode(240 * windowScaleFactor, 292 * windowScaleFactor), "Joust");
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

        window.clear();


        window.display();
    }
}

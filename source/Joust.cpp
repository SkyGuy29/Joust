#include "Joust.h"


Joust::Joust()
{
    window.create(sf::VideoMode(240 * windowScaleFactor, 292 * windowScaleFactor), "Joust");
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

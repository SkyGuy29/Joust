#include "Joust.h"


Joust::Joust()
{
    window.create(sf::VideoMode(WINDOW_X * WINDOW_SCALE, WINDOW_Y * WINDOW_SCALE), "Joust");
    window.setFramerateLimit(FPS);
}


void Joust::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();
        

        game.update();

        window.clear();

        game.drawTo(window);

        window.display();
    }
}

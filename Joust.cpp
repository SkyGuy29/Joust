#include "Joust.h"


const int windowMult = 3;


Joust::Joust()
{
    window.create(sf::VideoMode(240 * windowMult, 292 * windowMult), "Joust");
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

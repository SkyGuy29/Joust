#include <SFML/Graphics.hpp>


const int windowMult = 3;

int main()
{


    sf::RenderWindow window(sf::VideoMode(240 * windowMult, 292 * windowMult), "Joust");

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

    return 0;
}
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Solar System");
    window.setFramerateLimit(60);

    sf::CircleShape sun(30);
    sun.setPosition(400, 300);
    sun.setFillColor(sf::Color::Yellow);

    sf::CircleShape planets[] = {
        sf::CircleShape(5),  // Mercury
        sf::CircleShape(5),  // Venus
        sf::CircleShape(5),  // Earth
        sf::CircleShape(5),  // Mars
        sf::CircleShape(5),  // Jupiter
        sf::CircleShape(5),  // Saturn
        sf::CircleShape(5),  // Uranus
        sf::CircleShape(5)   // Neptune
    };

    double planetDistances[] = {0.39, 0.72, 1.0, 1.52, 5.20, 9.58, 19.18, 30.07};

    for (int i = 0; i < 8; i++) {
        planets[i].setFillColor(sf::Color::Blue);
        planets[i].setPosition(400 + planetDistances[i] * 50, 300);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(sun);
        for (int i = 0; i < 8; i++) {
            window.draw(planets[i]);
        }
        window.display();
    }

    return 0;
}

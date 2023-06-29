#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Celestial Bodies");
    window.setFramerateLimit(60);

    std::map<std::string, std::tuple<float, float, float, float>> bodies = {
        {"Sun", {0, 0, 0, 20}},
        {"Mercury", {50, 0, 0, 5}},
        {"Venus", {70, 0, 0, 7}},
        {"Earth", {100, 0, 0, 7}},
        {"Mars", {150, 0, 0, 6}},
        {"Jupiter", {220, 0, 0, 18}},
        {"Saturn", {280, 0, 0, 15}},
        {"Uranus", {350, 0, 0, 12}},
        {"Neptune", {400, 0, 0, 12}}
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        sf::CircleShape bodyShape;
        for (const auto& body : bodies)
        {
            bodyShape.setRadius(std::get<3>(body.second));
            bodyShape.setPosition(std::get<0>(body.second), std::get<1>(body.second));
            bodyShape.setFillColor(sf::Color::White);
            window.draw(bodyShape);
        }
        window.display();
    }

    return 0;
}

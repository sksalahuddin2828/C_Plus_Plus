// Make sure you have the SFML library installed and properly linked with your project. 
// Compile the code and run the executable. 
// The application window will display the circular motion animation with rotating balls.

#include <SFML/Graphics.hpp>
#include <cmath>

const int intervalTime = 40;
const int balls = 8;
const int maxStep = 64;

void animateWorld(sf::RenderWindow& window) {
    window.clear();

    sf::CircleShape baseShape(240.f);
    baseShape.setFillColor(sf::Color::Black);
    baseShape.setPosition(window.getSize().x / 2 - 240.f, window.getSize().y / 2 - 240.f);
    window.draw(baseShape);

    float elapsedTime = 0.f;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        elapsedTime = clock.getElapsedTime().asSeconds();
        int step = static_cast<int>((elapsedTime * 1000 / intervalTime) % maxStep);
        float centerX = window.getSize().x / 2 + 115.f * std::cos(step * 2.f / maxStep * M_PI);
        float centerY = window.getSize().y / 2 + 115.f * std::sin(step * 2.f / maxStep * M_PI);

        for (int i = 0; i < balls; i++) {
            float x = centerX + 115.f * std::cos((i * 2.f / balls - step * 2.f / maxStep) * M_PI);
            float y = centerY + 115.f * std::sin((i * 2.f / balls - step * 2.f / maxStep) * M_PI);

            sf::CircleShape circle(10.f);
            circle.setFillColor(sf::Color::White);
            circle.setPosition(x - 10.f, y - 10.f);
            window.draw(circle);
        }

        window.display();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circular Motion Animation");
    animateWorld(window);

    return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1850;
const int SCREEN_HEIGHT = 1850;
const int SUN_RADIUS = 50;

struct CelestialBody {
    std::string name;
    int radius;
    int orbit_radius;
    double orbit_speed;
    sf::Color color;
    double angle;

    CelestialBody(const std::string& name, int radius, int orbit_radius, double orbit_speed, const sf::Color& color)
        : name(name), radius(radius), orbit_radius(orbit_radius), orbit_speed(orbit_speed), color(color), angle(0) {}

    void update(double dt) {
        angle += orbit_speed * dt;
    }

    sf::Vector2f getPosition() {
        float x = SCREEN_WIDTH / 2 + std::cos(angle) * orbit_radius;
        float y = SCREEN_HEIGHT / 2 + std::sin(angle) * orbit_radius;
        return sf::Vector2f(x, y);
    }

    void draw(sf::RenderWindow& window) {
        sf::Vector2f position = getPosition();

        // Draw planet
        sf::CircleShape planet(radius);
        planet.setFillColor(color);
        planet.setPosition(position - sf::Vector2f(radius, radius));
        window.draw(planet);

        // Draw planet name
        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Failed to load font" << std::endl;
            return;
        }
        sf::Text text(name, font, 20);
        text.setFillColor(sf::Color::White);
        text.setPosition(position - sf::Vector2f(radius, radius + 20));
        window.draw(text);

        // Draw orbit circle
        sf::CircleShape orbit(orbit_radius, 100);
        orbit.setFillColor(sf::Color::Transparent);
        orbit.setOutlineColor(color);
        orbit.setOutlineThickness(1);
        orbit.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - orbit_radius, SCREEN_HEIGHT / 2 - orbit_radius));
        window.draw(orbit);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Solar System Simulator");

    std::vector<CelestialBody> planets = {
        {"Mercury", 10, 100, 0.2, sf::Color(169, 169, 169)},    // Gray
        {"Venus", 15, 150, 0.15, sf::Color(255, 165, 0)},        // Orange
        {"Earth", 20, 200, 0.1, sf::Color(0, 0, 255)},           // Blue
        {"Mars", 17, 250, 0.08, sf::Color(255, 0, 0)},           // Red
        {"Jupiter", 40, 350, 0.05, sf::Color(255, 215, 0)},      // Gold
        {"Saturn", 35, 450, 0.04, sf::Color(210, 180, 140)},     // Tan
        {"Uranus", 30, 550, 0.03, sf::Color(0, 255, 255)},       // Cyan
        {"Neptune", 30, 650, 0.02, sf::Color(0, 0, 139)},        // Dark Blue
        {"Pluto", 8, 750, 0.01, sf::Color(160, 82, 45)}          // Brown
    };

    CelestialBody sun("Sun", SUN_RADIUS, 0, 0, sf::Color::Yellow);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Time dt = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (auto& planet : planets) {
            planet.update(dt.asSeconds());
        }

        window.clear(sf::Color::Black);

        for (const auto& planet : planets) {
            planet.draw(window);
        }

        sun.draw(window);

        window.display();
    }

    return 0;
}

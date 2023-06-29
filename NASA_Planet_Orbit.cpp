#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 1800;
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

    sf::Vector2f getPosition() const {
        float x = SCREEN_WIDTH / 2 + std::cos(angle) * orbit_radius;
        float y = SCREEN_HEIGHT / 2 + std::sin(angle) * orbit_radius;
        return sf::Vector2f(x, y);
    }

    void draw(sf::RenderWindow& window) const {
        sf::Vector2f position = getPosition();

        // Draw planet
        sf::CircleShape planet(radius);
        planet.setFillColor(color);
        planet.setPosition(position.x - radius, position.y - radius);
        window.draw(planet);

        // Draw planet name
        sf::Text nameText(name, sf::Font::getDefaultFont(), 12);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(position.x - radius, position.y - radius - 20);
        window.draw(nameText);

        // Draw orbit circle
        sf::CircleShape orbit(orbit_radius, 100);
        orbit.setFillColor(sf::Color::Transparent);
        orbit.setOutlineColor(color);
        orbit.setOutlineThickness(1);
        orbit.setOrigin(orbit_radius, orbit_radius);
        orbit.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        window.draw(orbit);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Solar System Simulator");

    CelestialBody sun("Sun", SUN_RADIUS, 0, 0, sf::Color::Yellow);

    std::vector<CelestialBody> planets = {
        CelestialBody("Mercury", 10, 100, 0.02, sf::Color(169, 169, 169)),  // Gray
        CelestialBody("Venus", 15, 150, 0.015, sf::Color(255, 165, 0)),    // Orange
        CelestialBody("Earth", 20, 200, 0.01, sf::Color::Blue),
        CelestialBody("Mars", 17, 250, 0.008, sf::Color::Red),
        CelestialBody("Jupiter", 40, 350, 0.005, sf::Color(255, 215, 0)),  // Gold
        CelestialBody("Saturn", 35, 450, 0.004, sf::Color(210, 180, 140)), // Tan
        CelestialBody("Uranus", 30, 550, 0.003, sf::Color::Cyan),
        CelestialBody("Neptune", 30, 650, 0.002, sf::Color(0, 0, 139)),    // Dark Blue
        CelestialBody("Pluto", 8, 750, 0.001, sf::Color(165, 42, 42))      // Brown
    };

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        double dt = clock.restart().asSeconds();

        for (auto& planet : planets) {
            planet.update(dt);
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

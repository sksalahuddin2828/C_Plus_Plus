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

    double calculateVolume() {
        double volume = (4.0 / 3.0) * M_PI * std::pow(radius, 3);
        return volume;
    }

    double calculateSurfaceArea() {
        double surface_area = 4.0 * M_PI * std::pow(radius, 2);
        return surface_area;
    }

    double calculateOrbitalVelocity() {
        if (orbit_speed == 0) {
            return std::numeric_limits<double>::infinity();
        }
        double orbital_velocity = 2 * M_PI * orbit_radius / orbit_speed;
        return orbital_velocity;
    }
};

void drawCelestialBody(sf::RenderWindow& window, const CelestialBody& body) {
    sf::Vector2f position = body.getPosition();

    // Display the name
    sf::Text nameText(body.name, sf::Font::getDefaultFont(), 16);
    nameText.setFillColor(sf::Color::White);
    nameText.setPosition(position.x, position.y + body.radius + 20);
    window.draw(nameText);

    // Perform scientific calculations for each planet
    double volume = body.calculateVolume();
    double surfaceArea = body.calculateSurfaceArea();
    double orbitalVelocity = body.calculateOrbitalVelocity();

    // Display the calculations on console
    std::cout << "Planet: " << body.name << std::endl;
    std::cout << "Volume: " << volume << std::endl;
    std::cout << "Surface Area: " << surfaceArea << std::endl;
    std::cout << "Orbital Velocity: " << orbitalVelocity << std::endl;
    std::cout << "-------------------" << std::endl;

    // Draw the body
    sf::CircleShape planetShape(body.radius);
    planetShape.setOrigin(body.radius, body.radius);
    planetShape.setPosition(position);
    planetShape.setFillColor(body.color);
    window.draw(planetShape);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Planetary System");
    sf::Clock clock;

    CelestialBody sun("Sun", SUN_RADIUS, 0, 0, sf::Color(255, 255, 0));

    std::vector<CelestialBody> planets = {
        CelestialBody("Mercury", 10, 100, 0.02, sf::Color(128, 128, 128)),
        CelestialBody("Venus", 15, 150, 0.015, sf::Color(255, 165, 0)),
        CelestialBody("Earth", 20, 200, 0.01, sf::Color(0, 0, 255)),
        CelestialBody("Mars", 17, 250, 0.008, sf::Color(255, 0, 0)),
        CelestialBody("Jupiter", 40, 350, 0.005, sf::Color(255, 215, 0)),
        CelestialBody("Saturn", 35, 450, 0.004, sf::Color(210, 180, 140)),
        CelestialBody("Uranus", 30, 550, 0.003, sf::Color(0, 255, 255)),
        CelestialBody("Neptune", 30, 650, 0.002, sf::Color(0, 0, 139)),
        CelestialBody("Pluto", 8, 750, 0.001, sf::Color(165, 42, 42))
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time dt = clock.restart();

        window.clear(sf::Color::Black);

        for (auto& planet : planets) {
            planet.update(dt.asSeconds());
            drawCelestialBody(window, planet);
        }

        drawCelestialBody(window, sun);

        window.display();
    }

    return 0;
}

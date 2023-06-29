#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 2160;
const int SCREEN_HEIGHT = 2160;
const int SUN_RADIUS = 50;

// Planet data: name, radius, orbit radius, orbit speed, color
const std::vector<std::tuple<std::string, int, int, double, sf::Color>> PLANETS = {
    {"Mercury", 10, 100, 0.02, sf::Color(128, 128, 128)},
    {"Venus", 15, 150, 0.015, sf::Color(255, 165, 0)},
    {"Earth", 20, 200, 0.01, sf::Color(0, 0, 255)},
    {"Mars", 17, 250, 0.008, sf::Color(255, 0, 0)},
    {"Jupiter", 40, 350, 0.005, sf::Color(255, 215, 0)},
    {"Saturn", 35, 450, 0.004, sf::Color(210, 180, 140)},
    {"Uranus", 30, 550, 0.003, sf::Color(0, 255, 255)},
    {"Neptune", 30, 650, 0.002, sf::Color(0, 0, 139)},
    {"Pluto", 8, 750, 0.001, sf::Color(165, 42, 42)}
};

class CelestialBody {
public:
    CelestialBody(const std::string& name, int radius, int orbit_radius, double orbit_speed, const sf::Color& color)
        : name(name), radius(radius), orbit_radius(orbit_radius), orbit_speed(orbit_speed), color(color), angle(0) {}

    void update(double dt) {
        angle += orbit_speed * dt;
    }

    sf::Vector2f get_position() const {
        float x = SCREEN_WIDTH / 2 + std::cos(angle) * orbit_radius;
        float y = SCREEN_HEIGHT / 2 + std::sin(angle) * orbit_radius;
        return sf::Vector2f(x, y);
    }

    double calculate_volume() const {
        double volume = (4.0 / 3.0) * M_PI * std::pow(radius, 3);
        return volume;
    }

    double calculate_surface_area() const {
        double surface_area = 4 * M_PI * std::pow(radius, 2);
        return surface_area;
    }

    double calculate_orbital_velocity() const {
        if (orbit_speed == 0) {
            return INFINITY;
        }
        double orbital_velocity = 2 * M_PI * orbit_radius / orbit_speed;
        return orbital_velocity;
    }

    void draw(sf::RenderWindow& window) const {
        sf::Vector2f position = get_position();

        // Draw the body
        sf::CircleShape body(radius);
        body.setFillColor(color);
        body.setPosition(position.x - radius, position.y - radius);
        window.draw(body);

        // Display the name
        sf::Text name_text(name, sf::Font::getDefaultFont(), 16);
        name_text.setFillColor(sf::Color::White);
        name_text.setPosition(position.x, position.y + radius + 20);
        window.draw(name_text);

        // Perform scientific calculations for each planet
        double volume = calculate_volume();
        double surface_area = calculate_surface_area();
        double orbital_velocity = calculate_orbital_velocity();

        // Display the calculations
        sf::Text volume_text("Volume: " + std::to_string(volume), sf::Font::getDefaultFont(), 14);
        volume_text.setFillColor(sf::Color::White);
        volume_text.setPosition(position.x, position.y + radius + 40);
        window.draw(volume_text);

        sf::Text surface_area_text("Surface Area: " + std::to_string(surface_area), sf::Font::getDefaultFont(), 14);
        surface_area_text.setFillColor(sf::Color::White);
        surface_area_text.setPosition(position.x, position.y + radius + 55);
        window.draw(surface_area_text);

        sf::Text orbital_velocity_text("Orbital Velocity: " + std::to_string(orbital_velocity), sf::Font::getDefaultFont(), 14);
        orbital_velocity_text.setFillColor(sf::Color::White);
        orbital_velocity_text.setPosition(position.x, position.y + radius + 70);
        window.draw(orbital_velocity_text);
    }

private:
    std::string name;
    int radius;
    int orbit_radius;
    double orbit_speed;
    sf::Color color;
    double angle;
};

CelestialBody create_celestial_body(const std::string& name, int radius, int orbit_radius, double orbit_speed, const sf::Color& color) {
    return CelestialBody(name, radius, orbit_radius, orbit_speed, color);
}

void draw_celestial_body(sf::RenderWindow& window, const CelestialBody& body) {
    body.draw(window);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Planetary System");
    sf::Clock clock;

    CelestialBody sun("Sun", SUN_RADIUS, 0, 0, sf::Color(255, 255, 0));
    std::vector<CelestialBody> planets;

    for (const auto& planet_data : PLANETS) {
        std::string name;
        int radius, orbit_radius;
        double orbit_speed;
        sf::Color color;
        std::tie(name, radius, orbit_radius, orbit_speed, color) = planet_data;
        CelestialBody planet = create_celestial_body(name, radius, orbit_radius, orbit_speed, color);
        planets.push_back(planet);
    }

    bool is_running = true;

    while (is_running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                is_running = false;
        }

        double dt = clock.restart().asSeconds();

        window.clear(sf::Color::Black);

        for (auto& planet : planets) {
            planet.update(dt);
            draw_celestial_body(window, planet);
        }

        draw_celestial_body(window, sun);

        window.display();
    }

    return 0;
}

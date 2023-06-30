// Make sure you have the SFML library installed and set up in your C++ environment.
// Then, compile and run the code, and you will see a window displaying the circle dance animation with turtles moving in a circular pattern.


#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <random>

constexpr float PI = 3.14159265f;

class Turtle {
public:
    Turtle(float heading, int population) : heading(heading), size(2.f) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.f, 255.f);

        color = sf::Color(dis(gen) * 0.9f, 127.f + dis(gen) * 0.5f, dis(gen) * 0.7f);
    }

    void draw(sf::RenderWindow& window, float phase, int loops, int flip, float radius) {
        float individualPhase = fmodf(phase + heading * loops, 2.f * PI);
        float distance = radius * sinf(individualPhase);
        float x = window.getSize().x / 2 + cosf(heading) * distance;
        float y = window.getSize().y / 2 + sinf(heading) * distance;

        sf::CircleShape turtleShape(size);
        turtleShape.setFillColor(color);
        turtleShape.setPosition(x, y);
        turtleShape.setOrigin(size, size);

        if (flip == 1 && PI / 2.f < individualPhase && individualPhase <= 3.f * PI / 2.f) {
            turtleShape.setRotation(180.f);
        }

        window.draw(turtleShape);
    }

private:
    float heading;
    float size;
    sf::Color color;
};

void arrangeLines(sf::RenderWindow& window, int population, float radius) {
    sf::VertexArray lines(sf::Lines, population * 2);
    sf::Vector2u windowSize = window.getSize();

    for (int n = 0; n < population; ++n) {
        float angle = n / static_cast<float>(population) * PI;
        float x = windowSize.x / 2 + cosf(angle) * radius;
        float y = windowSize.y / 2 + sinf(angle) * radius;

        lines[n * 2].position = sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f);
        lines[n * 2 + 1].position = sf::Vector2f(x, y);
        lines[n * 2].color = sf::Color::White;
        lines[n * 2 + 1].color = sf::Color::White;
    }

    window.draw(lines);
}

int main() {
    int population = 11;
    int resolution = 480;
    int loops = 1;
    int flip = 0;
    int lines = 0;
    float radius = 250.f;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Dance Animation");
    window.setFramerateLimit(60);

    std::vector<Turtle> turtles;
    turtles.reserve(population);
    for (int i = 0; i < population; ++i) {
        float heading = i / static_cast<float>(population) * PI;
        turtles.emplace_back(heading, population);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        if (lines == 1) {
            arrangeLines(window, population, radius);
        }

        float phase = fmodf(window.getFrameTime() / (1.f / resolution), 2.f * PI);
        for (auto& turtle : turtles) {
            turtle.draw(window, phase, loops, flip, radius);
        }

        window.display();
    }

    return 0;
}

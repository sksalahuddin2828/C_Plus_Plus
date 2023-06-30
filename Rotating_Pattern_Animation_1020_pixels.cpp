// Compile the code with SFML libraries linked (e.g., -lsfml-graphics -lsfml-window -lsfml-system), and run the resulting executable.
// You will see a window displaying the rotating pattern animation with ball rotation visualization.


#include <SFML/Graphics.hpp>
#include <cmath>

const int WIDTH = 1020;
const int HEIGHT = 1020;
const int BALL_RADIUS = 15;
const int CIRCLE_RADIUS = 480;
const int LINE_COUNT = 24;

class RotatingPatternAnimation {
public:
    RotatingPatternAnimation() : window(sf::VideoMode(WIDTH, HEIGHT), "Rotating Pattern") {
        window.setVerticalSyncEnabled(true);
        window.setFramerateLimit(60);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    double angle = 0.0;
    sf::CircleShape baseCircle;
    sf::CircleShape balls[12];
    sf::Vertex lines[24 * 2];

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update() {
        angle += 0.01;
    }

    void render() {
        window.clear(sf::Color::Black);

        // Draw base circle
        baseCircle.setRadius(CIRCLE_RADIUS);
        baseCircle.setOutlineThickness(1.0);
        baseCircle.setOutlineColor(sf::Color::White);
        baseCircle.setFillColor(sf::Color::Black);
        baseCircle.setOrigin(CIRCLE_RADIUS, CIRCLE_RADIUS);
        baseCircle.setPosition(WIDTH / 2, HEIGHT / 2);
        window.draw(baseCircle);

        // Draw lines
        for (int i = 0; i < LINE_COUNT; i++) {
            double angle = (i / static_cast<double>(LINE_COUNT)) * 2 * M_PI;
            double x = WIDTH / 2 + CIRCLE_RADIUS * cos(angle);
            double y = HEIGHT / 2 + CIRCLE_RADIUS * sin(angle);
            lines[i * 2] = sf::Vertex(sf::Vector2f(WIDTH / 2, HEIGHT / 2), sf::Color::White);
            lines[i * 2 + 1] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
        }
        window.draw(lines, LINE_COUNT * 2, sf::Lines);

        // Draw rotating balls
        for (int i = 0; i < 12; i++) {
            double a = (i / static_cast<double>(12)) * 2 * M_PI;
            double x = WIDTH / 2 + cos(a) * (CIRCLE_RADIUS - BALL_RADIUS);
            double y = HEIGHT / 2 + sin(a) * (CIRCLE_RADIUS - BALL_RADIUS);
            balls[i].setRadius(BALL_RADIUS);
            balls[i].setOrigin(BALL_RADIUS, BALL_RADIUS);
            balls[i].setPosition(x, y);
            balls[i].setFillColor(sf::Color::White);

            if (i >= 6) {
                double innerAngle = a + angle;
                double rangeVal = cos(innerAngle);
                x = WIDTH / 2 + cos(a) * (CIRCLE_RADIUS - BALL_RADIUS - 1) * rangeVal;
                y = HEIGHT / 2 + sin(a) * (CIRCLE_RADIUS - BALL_RADIUS - 1) * rangeVal;
                balls[i].setPosition(x, y);
            }

            window.draw(balls[i]);
        }

        window.display();
    }
};

int main() {
    RotatingPatternAnimation animation;
    animation.run();

    return 0;
}

#include <SFML/Graphics.hpp>

class Turtle : public sf::Drawable {
private:
    sf::VertexArray lines;
    sf::Color penColor;
    float penWidth;
    bool penDown;

public:
    Turtle() {
        penColor = sf::Color::White;
        penWidth = 1.0f;
        penDown = true;
    }

    void setPenColor(const sf::Color& color) {
        penColor = color;
    }

    void setPenWidth(float width) {
        penWidth = width;
    }

    void penUp() {
        penDown = false;
    }

    void penDown() {
        penDown = true;
    }

    void goTo(float x, float y) {
        if (penDown) {
            lines.append(sf::Vertex(sf::Vector2f(x, y), penColor));
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(lines, states);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Turtle Graphics");

    Turtle turtle;
    turtle.setPenColor(sf::Color::White);
    turtle.setPenWidth(1.0f);
    turtle.penUp();
    turtle.goTo(-50, 60);
    turtle.penDown();
    turtle.goTo(100, 100);
    turtle.goTo(100, -100);
    turtle.goTo(-50, -60);
    turtle.goTo(-50, 60);
    turtle.goTo(15, 100);
    turtle.goTo(15, -100);
    turtle.penUp();
    turtle.goTo(100, 0);
    turtle.penDown();
    turtle.goTo(-100, 0);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(turtle);
        window.display();
    }

    return 0;
}

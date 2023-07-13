#include <SFML/Graphics.hpp>

const int FrameWidth = 800;
const int FrameHeight = 600;
const int RotationInterval = 20;

int main()
{
    sf::RenderWindow window(sf::VideoMode(FrameWidth, FrameHeight), "3D Earth Rotation");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("blue_marble.jpg")) {
        return -1; // Failed to load the Blue Marble image
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(FrameWidth / 2.0f, FrameHeight / 2.0f);

    int frameCount = 180;
    int frameDelay = RotationInterval;
    for (int frame = 0; frame < frameCount; frame++)
    {
        sprite.setRotation(frame);
        window.clear();
        window.draw(sprite);
        window.display();

        sf::sleep(sf::milliseconds(frameDelay));
    }

    return 0;
}

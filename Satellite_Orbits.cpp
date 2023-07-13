#include <cmath>
#include <cstdlib>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

const double EarthRadius = 6371; // Earth radius in kilometers
const int NumSatellites = 10;
const double SatelliteRadius = 100; // Satellite radius in kilometers
const sf::Color SatelliteColor = sf::Color::Red;

class SatelliteOrbits : public sf::Drawable
{
public:
    SatelliteOrbits()
    {
        // Generate random semi-major axes and eccentricities for satellite orbits
        std::random_device rd;
        std::default_random_engine engine(rd());
        std::uniform_real_distribution<double> semiMajorAxisDist(800, 1500);
        std::uniform_real_distribution<double> eccentricityDist(0.1, 0.4);

        for (int i = 0; i < NumSatellites; i++)
        {
            semiMajorAxes.push_back(semiMajorAxisDist(engine));
            eccentricities.push_back(eccentricityDist(engine));
        }

        // Time array
        numFrames = 100;
        time.resize(numFrames);
        double step = 2 * M_PI / numFrames;

        for (int i = 0; i < numFrames; i++)
        {
            time[i] = i * step;
        }
    }

private:
    std::vector<double> semiMajorAxes;
    std::vector<double> eccentricities;
    int numFrames;
    std::vector<double> time;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        // Plotting the Earth
        int width = target.getSize().x;
        int height = target.getSize().y;

        double xScale = width / 2.0 / EarthRadius;
        double yScale = height / 2.0 / EarthRadius;
        double zScale = std::min(xScale, yScale);

        double xCenter = width / 2.0;
        double yCenter = height / 2.0;

        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                double u = i * 2 * M_PI / 100;
                double v = j * M_PI / 50;
                double x = xCenter + EarthRadius * std::cos(u) * std::sin(v) * xScale;
                double y = yCenter + EarthRadius * std::sin(u) * std::sin(v) * yScale;
                double z = EarthRadius * std::cos(v) * zScale;
                sf::RectangleShape pixel(sf::Vector2f(1, 1));
                pixel.setPosition(static_cast<float>(x), static_cast<float>(y));
                pixel.setFillColor(sf::Color::Blue);
                target.draw(pixel);
            }
        }

        // Plotting the satellite orbits and markers
        for (int i = 0; i < NumSatellites; i++)
        {
            double semiMajorAxis = semiMajorAxes[i];
            double eccentricity = eccentricities[i];

            // Parametric equations for satellite orbit
            std::vector<double> r(numFrames);
            std::vector<double> xSatellite(numFrames);
            std::vector<double> ySatellite(numFrames);
            std::vector<double> zSatellite(numFrames);

            for (int j = 0; j < numFrames; j++)
            {
                r[j] = semiMajorAxis * (1 - eccentricity * eccentricity) / (1 + eccentricity * std::cos(time[j]));
                xSatellite[j] = xCenter + r[j] * std::cos(time[j]) * xScale;
                ySatellite[j] = yCenter + r[j] * std::sin(time[j]) * yScale;
                zSatellite[j] = 0;
            }

            for (int j = 1; j < numFrames; j++)
            {
                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f(static_cast<float>(xSatellite[j - 1]), static_cast<float>(ySatellite[j - 1])), sf::Color::Gray),
                    sf::Vertex(sf::Vector2f(static_cast<float>(xSatellite[j]), static_cast<float>(ySatellite[j])), sf::Color::Gray)
                };
                target.draw(line, 2, sf::Lines);
            }

            // Plotting the satellite markers
            sf::CircleShape marker(SatelliteRadius);
            marker.setFillColor(SatelliteColor);
            marker.setOrigin(SatelliteRadius, SatelliteRadius);
            marker.setPosition(static_cast<float>(xSatellite[numFrames - 1]), static_cast<float>(ySatellite[numFrames - 1]));
            target.draw(marker);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Satellite Orbits");

    SatelliteOrbits satelliteOrbits;
    window.draw(satelliteOrbits);
    window.display();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    return 0;
}

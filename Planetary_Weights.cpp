#include <iostream>
#include <string>
#include <cmath>

const double MERCURY_GRAVITY = 0.376;
const double VENUS_GRAVITY = 0.889;
const double MARS_GRAVITY = 0.378;
const double JUPITER_GRAVITY = 2.36;
const double SATURN_GRAVITY = 1.081;
const double URANUS_GRAVITY = 0.815;
const double NEPTUNE_GRAVITY = 1.14;

std::string capitalize(std::string str)
{
    if (str.empty())
        return str;
    
    str[0] = std::toupper(str[0]);
    return str;
}

bool isValidPlanet(const std::string& planet)
{
    std::string validPlanets[] = { "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune" };
    for (const std::string& validPlanet : validPlanets)
    {
        if (validPlanet == planet)
            return true;
    }
    return false;
}

int main()
{
    double earthWeight;
    std::cout << "Enter a weight on Earth: ";
    std::cin >> earthWeight;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string planet;
    std::cout << "Enter a planet: ";
    std::getline(std::cin, planet);
    planet = capitalize(planet);

    while (!isValidPlanet(planet))
    {
        if (planet == "Earth")
        {
            std::cout << "Please select a planet other than Earth." << std::endl;
        }
        else
        {
            std::cout << "Error: " << planet << " is not a planet." << std::endl;
        }

        std::cout << "Enter a planet: ";
        std::getline(std::cin, planet);
        planet = capitalize(planet);
    }

    double planetWeight;

    if (planet == "Mercury")
    {
        planetWeight = earthWeight * MERCURY_GRAVITY;
    }
    else if (planet == "Venus")
    {
        planetWeight = earthWeight * VENUS_GRAVITY;
    }
    else if (planet == "Mars")
    {
        planetWeight = earthWeight * MARS_GRAVITY;
    }
    else if (planet == "Jupiter")
    {
        planetWeight = earthWeight * JUPITER_GRAVITY;
    }
    else if (planet == "Saturn")
    {
        planetWeight = earthWeight * SATURN_GRAVITY;
    }
    else if (planet == "Uranus")
    {
        planetWeight = earthWeight * URANUS_GRAVITY;
    }
    else
    {
        planetWeight = earthWeight * NEPTUNE_GRAVITY;
    }

    double roundedWeight = round(planetWeight * 100) / 100;

    std::cout << "The equivalent weight on " << planet << ": " << roundedWeight << std::endl;

    return 0;
}

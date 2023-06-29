// Please make sure to have the SDL2 and SDL2_ttf libraries installed and linked correctly in your C++ project. 
// Also, provide the arial.ttf font file in the same directory as the source code or update the font path accordingly.

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 1900;
const int SCREEN_HEIGHT = 1900;

const int SUN_RADIUS = 50;

// Planet data: name, radius, orbit radius, orbit speed, color
const std::vector<std::tuple<std::string, int, int, double, SDL_Color>> PLANETS = {
    std::make_tuple("Mercury", 10, 100, 0.02, {128, 128, 128}),
    std::make_tuple("Venus", 15, 150, 0.015, {255, 165, 0}),
    std::make_tuple("Earth", 20, 200, 0.01, {0, 0, 255}),
    std::make_tuple("Mars", 17, 250, 0.008, {255, 0, 0}),
    std::make_tuple("Jupiter", 40, 350, 0.005, {255, 215, 0}),
    std::make_tuple("Saturn", 35, 450, 0.004, {210, 180, 140}),
    std::make_tuple("Uranus", 30, 550, 0.003, {0, 255, 255}),
    std::make_tuple("Neptune", 30, 650, 0.002, {0, 0, 139}),
    std::make_tuple("Pluto", 8, 750, 0.001, {165, 42, 42})
};

class CelestialBody {
public:
    std::string name;
    int radius;
    int orbit_radius;
    double orbit_speed;
    SDL_Color color;
    double angle;

    CelestialBody(const std::string& name, int radius, int orbit_radius, double orbit_speed, const SDL_Color& color)
        : name(name), radius(radius), orbit_radius(orbit_radius), orbit_speed(orbit_speed), color(color), angle(0) {}

    void update(double dt) {
        angle += orbit_speed * dt;
    }

    std::pair<int, int> get_position() {
        int x = SCREEN_WIDTH / 2 + std::cos(angle) * orbit_radius;
        int y = SCREEN_HEIGHT / 2 + std::sin(angle) * orbit_radius;
        return std::make_pair(x, y);
    }

    double calculate_volume() {
        double volume = (4.0 / 3.0) * M_PI * std::pow(radius, 3);
        return volume;
    }

    double calculate_surface_area() {
        double surface_area = 4 * M_PI * std::pow(radius, 2);
        return surface_area;
    }

    double calculate_orbital_velocity() {
        if (orbit_speed == 0) {
            return std::numeric_limits<double>::infinity();
        }
        double orbital_velocity = 2 * M_PI * orbit_radius / orbit_speed;
        return orbital_velocity;
    }
};

CelestialBody create_celestial_body(const std::string& name, int radius, int orbit_radius, double orbit_speed, const SDL_Color& color) {
    return CelestialBody(name, radius, orbit_radius, orbit_speed, color);
}

void draw_celestial_body(SDL_Renderer* renderer, const CelestialBody& body) {
    auto [x, y] = body.get_position();

    // Perform scientific calculations for each planet
    double volume = body.calculate_volume();
    double surface_area = body.calculate_surface_area();
    double orbital_velocity = body.calculate_orbital_velocity();

    // Print calculations to console
    std::cout << "Scientific Calculations:" << std::endl;
    std::cout << "Planet: " << body.name << std::endl;
    std::cout << "Volume: " << std::fixed << std::setprecision(2) << volume << std::endl;
    std::cout << "Surface Area: " << std::fixed << std::setprecision(2) << surface_area << std::endl;
    std::cout << "Orbital Velocity: " << std::fixed << std::setprecision(2) << orbital_velocity << std::endl;
    std::cout << "------------------------" << std::endl;

    // Render the calculations as text on the screen
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_Rect rect;

    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* volumeSurface = TTF_RenderText_Solid(font, ("Volume: " + std::to_string(volume)).c_str(), textColor);
    SDL_Texture* volumeTexture = SDL_CreateTextureFromSurface(renderer, volumeSurface);
    SDL_QueryTexture(volumeTexture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = x - rect.w / 2;
    rect.y = y + body.radius + 20;
    SDL_RenderCopy(renderer, volumeTexture, nullptr, &rect);
    SDL_FreeSurface(volumeSurface);
    SDL_DestroyTexture(volumeTexture);

    SDL_Surface* surfaceAreaSurface = TTF_RenderText_Solid(font, ("Surface Area: " + std::to_string(surface_area)).c_str(), textColor);
    SDL_Texture* surfaceAreaTexture = SDL_CreateTextureFromSurface(renderer, surfaceAreaSurface);
    SDL_QueryTexture(surfaceAreaTexture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = x - rect.w / 2;
    rect.y = y + body.radius + 40;
    SDL_RenderCopy(renderer, surfaceAreaTexture, nullptr, &rect);
    SDL_FreeSurface(surfaceAreaSurface);
    SDL_DestroyTexture(surfaceAreaTexture);

    SDL_Surface* orbitalVelocitySurface = TTF_RenderText_Solid(font, ("Orbital Velocity: " + std::to_string(orbital_velocity)).c_str(), textColor);
    SDL_Texture* orbitalVelocityTexture = SDL_CreateTextureFromSurface(renderer, orbitalVelocitySurface);
    SDL_QueryTexture(orbitalVelocityTexture, nullptr, nullptr, &rect.w, &rect.h);
    rect.x = x - rect.w / 2;
    rect.y = y + body.radius + 60;
    SDL_RenderCopy(renderer, orbitalVelocityTexture, nullptr, &rect);
    SDL_FreeSurface(orbitalVelocitySurface);
    SDL_DestroyTexture(orbitalVelocityTexture);

    // Draw the body
    SDL_SetRenderDrawColor(renderer, body.color.r, body.color.g, body.color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawCircle(renderer, x, y, body.radius);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Planetary System", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("arial.ttf", 16);
    if (!font) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
        return 1;
    }

    CelestialBody sun = create_celestial_body("Sun", SUN_RADIUS, 0, 0, {255, 255, 0});
    std::vector<CelestialBody> planets;

    for (const auto& planetData : PLANETS) {
        const auto& [name, radius, orbit_radius, orbit_speed, color] = planetData;
        CelestialBody planet = create_celestial_body(name, radius, orbit_radius, orbit_speed, color);
        planets.push_back(planet);
    }

    bool isRunning = true;

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (auto& planet : planets) {
            planet.update(1.0 / 50.0);
            draw_celestial_body(renderer, planet);
        }

        draw_celestial_body(renderer, sun);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

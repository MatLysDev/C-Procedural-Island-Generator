#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Tile {
    std::string name;
    float height;      // Noise threshold
    sf::Color color;   // SFML RGBA 
};

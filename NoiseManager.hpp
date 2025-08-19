#pragma once
#include <SFML/Graphics.hpp>
#include "NoiseParams.hpp"
#include "Noise.hpp"         // your fractal noise generator
#include "IslandFalloff.hpp" // your falloff generator
#include "Tile.hpp"          // your tile definitions

class NoiseManager {
public:
    sf::Image GenerateIslandImage(const NoiseParams& params);
};

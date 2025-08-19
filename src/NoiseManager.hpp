#pragma once
#include <SFML/Graphics.hpp>
#include "NoiseParams.hpp"
#include "Noise.hpp"         // your fractal noise generator
#include "IslandFalloff.hpp" // your falloff generator
#include "TileManager.hpp"   

class NoiseManager {
public:
    //pass TileManager so tiles can be customized
    sf::Image GenerateIslandImage(const NoiseParams& params, TileManager& tileManager);
};

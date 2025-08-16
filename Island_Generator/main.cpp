#include <iostream>
#include <vector>
#include <random>
#include "Noise.h"          
#include "IslandFalloff.h"

int main() {
    // Parameters
    int   mapWidth = 10;
    int   mapHeight = 10;
    int   seed = 1;
    float scale = 50.0f;
    int   octaves = 7;
    float persistance = 0.5f;
    float lacunarity = 2.0f;

    int   minIslands = 3;
    int   maxIslands = 6;
    float minIslandSizeFactor = 0.2f;
    float maxIslandSizeFactor = 0.4f;

    // Optionally randomise seed
    bool randomizeSeed = true;

    if (randomizeSeed) {
        std::random_device rd;
        seed = static_cast<int>(rd());
    }

    // Create generator objects 
    NoiseGenerator  fractalNoise;  
    IslandFalloff   falloff;       

    // Generate noise map
    std::vector<std::vector<float>> noiseMap =
        fractalNoise.GenerateNoiseMap(
            mapWidth, mapHeight, seed, scale,
            octaves, persistance, lacunarity
        );

    // Generate falloff map
    std::vector<std::vector<float>> falloffMap =
        falloff.GenerateFalloffMap(
            mapWidth, mapHeight, seed,
            minIslands, maxIslands,
            minIslandSizeFactor, maxIslandSizeFactor
        );

    // Apply falloff to noise map
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            noiseMap[x][y] *= (1.0f - falloffMap[x][y]);
        }
    }

    // Print it out
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            std::cout << noiseMap[x][y] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}

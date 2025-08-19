#pragma once
#include <vector>

// Generates 2D noise maps for terrain using multiple octaves
class NoiseGenerator {
public:
    // Returns a 2D vector of floats normalized between 0 and 1
    static std::vector<std::vector<float>> GenerateNoiseMap(
        int mapWidth,
        int mapHeight,
        int seed,
        float scale,
        int octaves,
        float persistence,
        float lacunarity
    );
};

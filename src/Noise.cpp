#include "Noise.hpp"
#include "FastNoiseLite.h" 
#include <algorithm> 

std::vector<std::vector<float>> NoiseGenerator::GenerateNoiseMap(
    int mapWidth,
    int mapHeight,
    int seed,
    float scale,
    int octaves,
    float persistence,
    float lacunarity
) {
    // Create a 2D vector to hold the noise map
    std::vector<std::vector<float>> noiseMap(mapWidth, std::vector<float>(mapHeight));

    // Initialize FastNoiseLite object
    FastNoiseLite noise;
    noise.SetSeed(seed);
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);

    // Avoid division by zero
    if (scale <= 0.0f)
        scale = 0.0001f;

    // Track min/max noise values for normalization
    float maxNoiseHeight = -999999.0f;
    float minNoiseHeight = 999999.0f;

    float halfWidth = mapWidth / 2.0f;
    float halfHeight = mapHeight / 2.0f;

    // Loop over each position in the map
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float noiseHeight = 0.0f;

            // Multi-octave (fractal) noise
            for (int i = 0; i < octaves; i++) {
                float sampleX = (x - halfWidth) / scale * frequency;
                float sampleY = (y - halfHeight) / scale * frequency;

                float value = noise.GetNoise(sampleX, sampleY); // returns -1..1
                noiseHeight += value * amplitude;

                amplitude *= persistence;
                frequency *= lacunarity;
            }

            // Track min/max for normalization
            maxNoiseHeight = std::max(maxNoiseHeight, noiseHeight);
            minNoiseHeight = std::min(minNoiseHeight, noiseHeight);

            noiseMap[x][y] = noiseHeight;
        }
    }

    // Normalize the map to [0,1]
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapWidth; x++) {
            noiseMap[x][y] = (noiseMap[x][y] - minNoiseHeight) / (maxNoiseHeight - minNoiseHeight);
        }
    }

    return noiseMap;
}

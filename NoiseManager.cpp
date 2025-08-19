#include "NoiseManager.hpp"
#include <vector>
#include <algorithm>

sf::Image NoiseManager::GenerateIslandImage(const NoiseParams& params) {
    NoiseGenerator fractalNoise;
    IslandFalloff falloff;

    // Generate base maps
    auto noiseMap = fractalNoise.GenerateNoiseMap(
        params.mapWidth, params.mapHeight, params.seed,
        params.scale, params.octaves, params.persistence, params.lacunarity
    );

    // Generate falloff using params (instead of hardcoding values)
    auto falloffMap = falloff.GenerateFalloffMap(
        params.mapWidth, params.mapHeight, params.seed,
        params.minIslands, params.maxIslands,
        params.minIslandSizeFactor, params.maxIslandSizeFactor
    );

    // Apply falloff
    for (int y = 0; y < params.mapHeight; y++) {
        for (int x = 0; x < params.mapWidth; x++) {
            noiseMap[x][y] *= (1.0f - falloffMap[x][y]);
        }
    }

    // Tiles
    std::vector<Tile> tilesVec = {
        {"DeepWater", 0.1f, {0,0,128,255}},
        {"ShallowWater", 0.2f, {0,0,255,255}},
        {"Sand", 0.3f, {194,178,128,255}},
        {"Grass", 0.5f, {0,255,0,255}},
        {"DarkGrass", 0.7f, {0,128,0,255}},
        {"Mountain", 1.0f, {128,128,128,255}}
    };
    std::sort(tilesVec.begin(), tilesVec.end(),
        [](const Tile& a, const Tile& b) { return a.height < b.height; });

    // Build final image
    sf::Image image;
    image.create(params.mapWidth, params.mapHeight);

    for (int y = 0; y < params.mapHeight; y++) {
        for (int x = 0; x < params.mapWidth; x++) {
            float v = noiseMap[x][y];
            sf::Color c = sf::Color::Black;
            for (auto& t : tilesVec) {
                if (v <= t.height) { c = t.color; break; }
            }
            image.setPixel(x, y, c);
        }
    }

    return image;
}

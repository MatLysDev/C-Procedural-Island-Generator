#pragma once

struct NoiseParams {
    int mapWidth = 500;
    int mapHeight = 500;
    int seed = 12345;
    float scale = 1.00F;
    int octaves = 7;
    float persistence = 0.5f;
    float lacunarity = 2.0f;
    int minIslands = 3;
    int maxIslands = 6;
    float minIslandSizeFactor = 0.2f;
    float maxIslandSizeFactor = 0.4f;
    bool autoUpdate = true;
    bool randomiseSeed = true;


    bool operator==(const NoiseParams& other) const {
        return mapWidth == other.mapWidth
            && mapHeight == other.mapHeight
            && seed == other.seed
            && scale == other.scale
            && octaves == other.octaves
            && persistence == other.persistence
            && lacunarity == other.lacunarity
            && minIslands == other.minIslands
            && maxIslands == other.maxIslands
            && minIslandSizeFactor == other.minIslandSizeFactor
            && maxIslandSizeFactor == other.maxIslandSizeFactor
            && autoUpdate == other.autoUpdate
            && randomiseSeed == other.randomiseSeed;
    }

    bool operator!=(const NoiseParams& other) const {
        return !(*this == other); // ! flip the == operator 
    };

};


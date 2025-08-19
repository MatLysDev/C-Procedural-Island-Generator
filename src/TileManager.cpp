#include "TileManager.hpp"

TileManager::TileManager() {
    tiles = {
        {"DeepWater", 0.1f, {0,0,128,255}},
        {"ShallowWater", 0.2f, {0,0,255,255}},
        {"Sand", 0.3f, {194,178,128,255}},
        {"Grass", 0.5f, {0,255,0,255}},
        {"DarkGrass", 0.7f, {0,128,0,255}},
        {"Mountain", 1.0f, {128,128,128,255}}
    };
}

void TileManager::Reset() {
    // Reset to default thresholds/colors
    *this = TileManager();
}

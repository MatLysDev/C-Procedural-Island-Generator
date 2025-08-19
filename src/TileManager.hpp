#pragma once
#include "Tile.hpp"
#include <vector>

class TileManager {
public:
    TileManager();
    void Reset();

    // Non-const version for editing tiles
    std::vector<Tile>& GetTiles() { return tiles; }

    // Const version for reading tiles
    const std::vector<Tile>& GetTiles() const { return tiles; }

private:
    std::vector<Tile> tiles;
};

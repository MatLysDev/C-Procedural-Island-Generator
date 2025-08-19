#pragma once
#include "NoiseParams.hpp"
#include <string>
#include <SFML/Graphics.hpp>
#include "TileManager.hpp"

namespace SaveManager {
    void SaveParams(const NoiseParams& params, const std::string& filename = "params.txt");
    bool LoadParams(NoiseParams& params, const std::string& filename = "params.txt");
    static void SavePNG(const sf::Texture& texture, const std::string& path);
    bool LoadTiles(TileManager& tileManager, const std::string& filename = "tiles.txt");
    void SaveTiles(const TileManager& tileManager, const std::string& filename = "tiles.txt");
}

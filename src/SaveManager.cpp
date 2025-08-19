#include "SaveManager.hpp"
#include <fstream>
#include "TileManager.hpp"
#include "Tile.hpp"

namespace SaveManager {
    void SaveParams(const NoiseParams& params, const std::string& filename) {
        std::ofstream out(filename);
        if (!out) return;

        out << params.seed << "\n";
        out << params.scale << "\n";
        out << params.octaves << "\n";
        out << params.persistence << "\n";
        out << params.lacunarity << "\n";
        out << params.autoUpdate << "\n";
        out << params.randomiseSeed << "\n";
        out << params.minIslands << "\n";
        out << params.maxIslands << "\n";
        
    }

    bool LoadParams(NoiseParams& params, const std::string& filename) {
        std::ifstream in(filename);
        if (!in) return false;

        in >> params.seed;
        in >> params.scale;
        in >> params.octaves;
        in >> params.persistence;
        in >> params.lacunarity;
        in >> params.autoUpdate;
        in >> params.randomiseSeed;
        in >> params.minIslands;
        in >> params.maxIslands;
        return true;
    }

    void SavePNG(const sf::Texture& texture, const std::string& filename) {
        sf::Image image = texture.copyToImage();
        image.saveToFile(filename);
    }
    void SaveTiles(const TileManager& tileManager, const std::string& filename) {
        std::ofstream out(filename);
        if (!out) return;

        for (const auto& tile : tileManager.GetTiles()) {
            out << tile.name << "\n";
            out << tile.height << "\n";
            out << (int)tile.color.r << " "
                << (int)tile.color.g << " "
                << (int)tile.color.b << " "
                << (int)tile.color.a << "\n";
        }
    }

    bool LoadTiles(TileManager& tileManager, const std::string& filename) {
        std::ifstream in(filename);
        if (!in) return false;

        auto& tiles = tileManager.GetTiles();
        tiles.clear();

        std::string name;
        float height;
        int r, g, b, a;
        while (in >> std::ws && std::getline(in, name)) {
            in >> height;
            in >> r >> g >> b >> a;
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            tiles.push_back({ name, height, sf::Color(r, g, b, a) });
        }

        return true;
    }
}

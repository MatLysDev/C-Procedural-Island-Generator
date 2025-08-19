#include "UIManager.hpp"
#include "imgui.h"

UIResult UIManager::Show(NoiseParams& params, TileManager& tileManager) {
    UIResult result;

    ImGui::Begin("Noise Controls");

    // --- Map size ---
    if (ImGui::CollapsingHeader("Map Size", ImGuiTreeNodeFlags_DefaultOpen)) {
        result.regenerate |= ImGui::SliderInt("Width", &params.mapWidth, 100, 2000);
        result.regenerate |= ImGui::InputInt("Width Input", &params.mapWidth);

        result.regenerate |= ImGui::SliderInt("Height", &params.mapHeight, 100, 2000);
        result.regenerate |= ImGui::InputInt("Height Input", &params.mapHeight);
    }

    // --- Seed ---
    if (ImGui::CollapsingHeader("Seed Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        result.regenerate |= ImGui::InputInt("Seed", &params.seed);
        result.regenerate |= ImGui::Checkbox("Randomise Seed", &params.randomiseSeed);
    }

    // --- Noise parameters ---
    if (ImGui::CollapsingHeader("Noise Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
        result.regenerate |= ImGui::SliderFloat("Scale", &params.scale, 0.001f, 200.0f);
        result.regenerate |= ImGui::InputFloat("Scale Input", &params.scale);

        result.regenerate |= ImGui::SliderInt("Octaves", &params.octaves, 1, 10);
        result.regenerate |= ImGui::InputInt("Octaves Input", &params.octaves);

        result.regenerate |= ImGui::SliderFloat("Persistence", &params.persistence, 0.0f, 1.0f);
        result.regenerate |= ImGui::InputFloat("Persistence Input", &params.persistence);

        result.regenerate |= ImGui::SliderFloat("Lacunarity", &params.lacunarity, 1.0f, 5.0f);
        result.regenerate |= ImGui::InputFloat("Lacunarity Input", &params.lacunarity);
    }

    // --- Island settings ---
    if (ImGui::CollapsingHeader("Island Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        result.regenerate |= ImGui::SliderInt("Min Islands", &params.minIslands, 1, 20);
        result.regenerate |= ImGui::InputInt("Min Islands Input", &params.minIslands);

        result.regenerate |= ImGui::SliderInt("Max Islands", &params.maxIslands, params.minIslands, 20);
        result.regenerate |= ImGui::InputInt("Max Islands Input", &params.maxIslands);

        result.regenerate |= ImGui::SliderFloat("Min Island Size", &params.minIslandSizeFactor, 0.01f, 1.0f);
        result.regenerate |= ImGui::InputFloat("Min Island Size Input", &params.minIslandSizeFactor);

        result.regenerate |= ImGui::SliderFloat("Max Island Size", &params.maxIslandSizeFactor, params.minIslandSizeFactor, 1.0f);
        result.regenerate |= ImGui::InputFloat("Max Island Size Input", &params.maxIslandSizeFactor);
    }

    // --- General ---
    if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::Button("Regenerate")) result.regenerate = true;

        // Input text with local std::string
        char buffer[128];
        std::snprintf(buffer, sizeof(buffer), "%s", result.saveFilename.c_str());
        if (ImGui::InputText("Filename", buffer, sizeof(buffer))) {
            result.saveFilename = buffer; // update UIResult string
        }

        if (ImGui::Button("Save PNG")) {
            result.savePNG = true;
            if (result.saveFilename.empty())
                result.saveFilename = "Island";
        }
    }

    ImGui::End();

    // --- Tile Editor ---
    ImGui::Begin("Tile Editor");

    for (auto& tile : tileManager.GetTiles()) {
        // Convert sf::Color to ImGui float[4] in 0-1 range
        ImVec4 col(tile.color.r / 255.f, tile.color.g / 255.f, tile.color.b / 255.f, tile.color.a / 255.f);

        // Edit the color in ImGui
        if (ImGui::ColorEdit4(tile.name.c_str(), (float*)&col)) {
            // Update the tile color safely
            tile.color.r = static_cast<sf::Uint8>(col.x * 255.f);
            tile.color.g = static_cast<sf::Uint8>(col.y * 255.f);
            tile.color.b = static_cast<sf::Uint8>(col.z * 255.f);
            tile.color.a = static_cast<sf::Uint8>(col.w * 255.f);
            result.regenerate = true;
        }

        // Edit the threshold/height
        if (ImGui::SliderFloat(("Threshold " + tile.name).c_str(), &tile.height, 0.0f, 1.0f)) {
            result.regenerate = true;
        }
    }

    // Reset button
    if (ImGui::Button("Reset Tiles")) {
        tileManager.Reset();
        result.regenerate = true;
    }

    ImGui::End();

    return result;
}

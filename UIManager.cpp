#include "UIManager.hpp"
#include "imgui.h"

bool UIManager::Show(NoiseParams& params) {
    bool regenerate = false;

    ImGui::Begin("Noise Controls");

    // Map size: slider + input
    regenerate |= ImGui::SliderInt("Width", &params.mapWidth, 100, 2000);
    regenerate |= ImGui::InputInt("Width Input", &params.mapWidth);

    regenerate |= ImGui::SliderInt("Height", &params.mapHeight, 100, 2000);
    regenerate |= ImGui::InputInt("Height Input", &params.mapHeight);

    // Seed
    regenerate |= ImGui::InputInt("Seed", &params.seed);
    regenerate |= ImGui::Checkbox("Randomise Seed", &params.randomiseSeed);

    // Noise parameters: slider + input
    regenerate |= ImGui::SliderFloat("Scale", &params.scale, 0.001f, 200.0f);
    regenerate |= ImGui::InputFloat("Scale Input", &params.scale);

    regenerate |= ImGui::SliderInt("Octaves", &params.octaves, 1, 10);
    regenerate |= ImGui::InputInt("Octaves Input", &params.octaves);

    regenerate |= ImGui::SliderFloat("Persistence", &params.persistence, 0.0f, 1.0f);
    regenerate |= ImGui::InputFloat("Persistence Input", &params.persistence);

    regenerate |= ImGui::SliderFloat("Lacunarity", &params.lacunarity, 1.0f, 5.0f);
    regenerate |= ImGui::InputFloat("Lacunarity Input", &params.lacunarity);

    // Island-specific parameters
    regenerate |= ImGui::SliderInt("Min Islands", &params.minIslands, 1, 20);
    regenerate |= ImGui::InputInt("Min Islands Input", &params.minIslands);

    regenerate |= ImGui::SliderInt("Max Islands", &params.maxIslands, params.minIslands, 20);
    regenerate |= ImGui::InputInt("Max Islands Input", &params.maxIslands);

    regenerate |= ImGui::SliderFloat("Min Island Size", &params.minIslandSizeFactor, 0.01f, 1.0f);
    regenerate |= ImGui::InputFloat("Min Island Size Input", &params.minIslandSizeFactor);

    regenerate |= ImGui::SliderFloat("Max Island Size", &params.maxIslandSizeFactor, params.minIslandSizeFactor, 1.0f);
    regenerate |= ImGui::InputFloat("Max Island Size Input", &params.maxIslandSizeFactor);

    // Auto-update checkbox
    ImGui::Separator();
    regenerate |= ImGui::Checkbox("Auto Update", &params.autoUpdate);

    // Manual regenerate button
    if (ImGui::Button("Regenerate")) regenerate = true;

    ImGui::End();
    return regenerate;
}

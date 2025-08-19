#include "WindowManager.hpp"
#include "NoiseManager.hpp"
#include "UIManager.hpp"
#include "NoiseParams.hpp"
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "TileManager.hpp"
#include "SaveManager.hpp"

int main() {
    // 1️ Create SFML window
    WindowManager window(800, 600, "Noise Island");

    // 2️ Initialize ImGui-SFML
    ImGui::SFML::Init(window.getRenderWindow());

    NoiseParams params;
    SaveManager::LoadParams(params);

    TileManager tileManager;
    SaveManager::LoadTiles(tileManager);

    NoiseParams prevParams = params; // store previous parameters
    NoiseManager noiseManager;
    UIManager uiManager;

    // 3️ Load initial texture
    sf::Texture texture;
    if (!texture.loadFromImage(noiseManager.GenerateIslandImage(params,tileManager))) {
        std::cerr << "Failed to generate initial island texture\n";
        return 1;
    }
    window.setTexture(texture);

    sf::Clock deltaClock;

    // 4️ Setup view for zoom/pan
    sf::View view(window.getRenderWindow().getDefaultView());

    // Mouse dragging state
    bool dragging = false;

    sf::Vector2i lastMousePos;

    // 5️ Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.getRenderWindow().pollEvent(event)) {
            // Forward events to ImGui
            ImGui::SFML::ProcessEvent(event);

            // Handle window close
            if (event.type == sf::Event::Closed)
            {
                SaveManager::SaveParams(params);
                SaveManager::SaveTiles(tileManager);
                window.getRenderWindow().close();
            }
            // Move island with mouse drag (only if not interacting with ImGui)
            if (!ImGui::GetIO().WantCaptureMouse) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window.getRenderWindow());

                    if (!dragging) {
                        dragging = true;
                        lastMousePos = mousePos;
                    }
                    else {
                        sf::Vector2i delta = mousePos - lastMousePos;
                        view.move(-delta.x, -delta.y);
                        lastMousePos = mousePos;
                    }
                }
                else {
                    dragging = false;
                }
            }

            // Zoom with scroll
            if (event.type == sf::Event::MouseWheelScrolled) {
                if (event.mouseWheelScroll.delta > 0) {
                    view.zoom(0.9f); // zoom in
                }
                else {
                    view.zoom(1.1f); // zoom out
                }
                window.getRenderWindow().setView(view);
            }

            // Reset view with R
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                // Get window size
                sf::Vector2u winSize = window.getRenderWindow().getSize();

                // Get texture size
                sf::Vector2u texSize = texture.getSize();

                // Create a view centered on the texture
                view.setCenter(texSize.x / 2.f, texSize.y / 2.f);
                view.setSize((float)winSize.x, (float)winSize.y);

                // Calculate scale factors
                float scaleX = static_cast<float>(winSize.x) / texSize.x;
                float scaleY = static_cast<float>(winSize.y) / texSize.y;

                // Use the smaller scale so the whole island fits
                float finalScale = std::min(scaleX, scaleY);
                view.zoom(1.f / finalScale);

                window.getRenderWindow().setView(view);
            }

        }

        // Update ImGui
        ImGui::SFML::Update(window.getRenderWindow(), deltaClock.restart());

        // Show UI and detect changes
        UIResult results = uiManager.Show(params,tileManager);

        // Only regenerate island if parameters changed and autoUpdate is enabled
        if (results.regenerate || (params.autoUpdate && params != prevParams)) {
            if (params.randomiseSeed) {
                params.seed = rand(); // generate a new random seed
            }

            if (!texture.loadFromImage(noiseManager.GenerateIslandImage(params,tileManager))) {
                std::cerr << "Failed to generate island texture\n";
            }
            else {
                window.setTexture(texture);
            }

            prevParams = params; // update previous copy
        }

        if (results.savePNG) {
            std::string filename = results.saveFilename.empty() ? "Island" : results.saveFilename;
            filename += ".png";  // always add .png extension

            if (!texture.copyToImage().saveToFile(filename))
                std::cerr << "Failed to save PNG\n";
            else
                std::cout << "Island saved to " << filename << "\n";
        }

        // Draw frame
        window.beginFrame();
        window.getRenderWindow().setView(view);  // apply current zoom/pan
        window.drawSprite();                     // draw island
        ImGui::SFML::Render(window.getRenderWindow());  // draw UI
        window.endFrame();
    }

    // 6️ Shutdown ImGui-SFML
    ImGui::SFML::Shutdown();

    return 0;
}



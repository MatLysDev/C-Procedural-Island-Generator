#pragma once
#include <SFML/Graphics.hpp>

class WindowManager {
public:
    WindowManager(int width, int height, const std::string& title);

    void processEvents();
    void beginFrame();
    void drawSprite();   // draws the internal sprite
    void endFrame();

    void setTexture(const sf::Texture& texture);
    bool isOpen() const;
    sf::RenderWindow& getRenderWindow(); // needed for ImGui-SFML

private:
    sf::RenderWindow _window;
    sf::Sprite _sprite;
};

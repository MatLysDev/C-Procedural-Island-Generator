#include "WindowManager.hpp"

WindowManager::WindowManager(int width, int height, const std::string& title)
    : _window(sf::VideoMode(width, height), title)
{
    _window.setFramerateLimit(30);
}

void WindowManager::processEvents() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
    }
}

void WindowManager::beginFrame() {
    _window.clear();
}

void WindowManager::drawSprite() {
    _window.draw(_sprite); 
}

void WindowManager::endFrame() {
    _window.display();
}

void WindowManager::setTexture(const sf::Texture& texture) {
    _sprite.setTexture(texture, true); 
}

bool WindowManager::isOpen() const {
    return _window.isOpen();
}

sf::RenderWindow& WindowManager::getRenderWindow() {
    return _window;
}

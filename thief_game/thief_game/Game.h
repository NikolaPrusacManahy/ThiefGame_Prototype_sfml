#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void handleEvent(const sf::Event& e); // SFML 2.6 path

#if (SFML_VERSION_MAJOR >= 3)
    void handleEvent3(const sf::Event& e); // SFML 3 path
#endif

    void update(sf::Time dt);
    void render();

    void setupFontAndText();
    void setupSprite();

private:
    sf::RenderWindow m_window;
    bool m_exitGame{ false };

    // Demo content (keep for sanity checks)
    sf::Font m_font;
    sf::Text m_title;

    sf::Texture m_logoTexture;
    std::optional<sf::Sprite> m_logoSprite;
};
#include "Game.h"
#include <iostream>

namespace
{
    constexpr unsigned WINDOW_W = 1200;
    constexpr unsigned WINDOW_H = 1000;
    constexpr float FPS = 60.0f;
}

Game::Game()
    : m_window(
        sf::VideoMode(sf::Vector2u{ WINDOW_W, WINDOW_H }),
        "SFML Game",
        sf::State::Windowed
    ) , m_title(m_font),
        m_player(m_assets)
    {
    m_window.setFramerateLimit(60);

    setupFontAndText();
    setupSprite();
    }

void Game::run()
{
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    const sf::Time dt = sf::seconds(1.0f / FPS);

    while (m_window.isOpen())
    {
        processEvents();

        accumulator += clock.restart();
        while (accumulator >= dt)
        {
            accumulator -= dt;
            update(dt);
        }

        render();
    }
}

void Game::processEvents()
{
#if (SFML_VERSION_MAJOR >= 3)
    // SFML 3: pollEvent() returns std::optional<sf::Event>
    while (auto ev = m_window.pollEvent())
    {
        handleEvent3(*ev);
    }
#else
    // SFML 2.6: pollEvent(sf::Event&)
    sf::Event ev;
    while (m_window.pollEvent(ev))
    {
        handleEvent(ev);
    }
#endif
}

void Game::handleEvent(const sf::Event& e)
{
    while (const std::optional event = m_window.pollEvent())
    {
        // close requested
        if (event->is<sf::Event::Closed>())
            m_window.close();

        // escape pressed
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Escape)
                m_window.close();
        }
    }
}

#if (SFML_VERSION_MAJOR >= 3)
void Game::handleEvent3(const sf::Event& e)
{
    // SFML 3 uses a different event model; this keeps it simple and future-proof.
    // Depending on your SFML 3 build, you may need to adapt the exact checks.
    // If you’re on SFML 2.6, this function is ignored anyway.

    // Safe fallback: close on window close request if your build supports it.
    // If your SFML 3 headers differ, tell me what your event struct looks like.
    if (e.is<sf::Event::Closed>())
    {
        m_window.close();
        return;
    }

    if (const auto* kp = e.getIf<sf::Event::KeyPressed>())
    {
        if (kp->code == sf::Keyboard::Key::Escape)
        {
            m_window.close();
            return;
        }
    }
}
#endif

void Game::update(sf::Time dt)
{
    float seconds = dt.asSeconds();
    
    m_player.handleInput();
    m_player.update(seconds);
    m_detectionUI.update(m_player.getDetectionGauge());
}

void Game::render()
{
    m_window.clear(sf::Color::White);
    
    m_player.render(m_window);
    m_detectionUI.render(m_window);

    m_window.display();
}

void Game::setupFontAndText()
{
    // Use forward slashes for portability (works on Windows too)
    if (!m_font.openFromFile("ASSETS/FONTS/ariblk.ttf"))
    {
        std::cout << "Error: could not load font ASSETS/FONTS/ariblk.ttf\n";
    }

    m_title.setFont(m_font);
    m_title.setString("SFML Game");
    m_title.setCharacterSize(72);
    m_title.setStyle(sf::Text::Bold | sf::Text::Italic | sf::Text::Underlined);
    m_title.setFillColor(sf::Color::Black);
    m_title.setOutlineColor(sf::Color::Red);
    m_title.setOutlineThickness(3.0f);
    m_title.setPosition(sf::Vector2f(40.0f, 40.0f));
}

void Game::setupSprite()
{
    // leave empty
}

#pragma once
#include<SFML/Graphics.hpp>

class DetectionUI
{
public:
	DetectionUI()
	{
		m_background.setSize({ 200.f,20.f });
		m_background.setFillColor(sf::Color(50, 50, 50));
		m_background.setPosition({ 20.f,20.f });

		m_fill.setSize({ 0.f,16.f });
		m_fill.setPosition({ 22.f,22.f });
	}

	void update(float detectionPercent)
	{
		float width = (detectionPercent / 100.f) * 196.f;
		m_fill.setSize({ width, 16.f });

		// color gradient
		if (detectionPercent < 40.f)
		{
			m_fill.setFillColor(sf::Color::Green);
		}
		else if (detectionPercent < 75.f)
		{
			m_fill.setFillColor(sf::Color::Yellow);
		}
		else
		{
			m_fill.setFillColor(sf::Color::Red);
		}
	}

	void render(sf::RenderWindow& window)
	{
		window.draw(m_background);
		window.draw(m_fill);
	}

private:
	sf::RectangleShape m_background;
	sf::RectangleShape m_fill;
};
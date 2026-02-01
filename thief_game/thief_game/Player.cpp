#include "Player.h"

Player::Player(AssetManager& t_assetManager):m_assetManager(t_assetManager)
{
	m_shape.setSize({ 32.f,32.f });
	m_shape.setFillColor(sf::Color::Green);
	m_shape.setOrigin({ 16.f,16.f });
	m_Position = { 400.f, 400.f };
}

void Player::handleInput()
{
	m_Velocity = { 0.f,0.f };

	// input for the movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_Velocity.y -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_Velocity.y += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_Velocity.x -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_Velocity.x += 1.f;
	}

	// for diagonal movement
	float length = std::sqrt(m_Velocity.x * m_Velocity.x + m_Velocity.y * m_Velocity.y);
	if (length > 0.f)
	{
		m_Velocity /= length;
	}

	updateState();
}

void Player::update(double dt)
{
}

void Player::render(sf::RenderWindow& window)
{
}

void Player::setPosition(sf::Vector2f t_position)
{
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f();
}

void Player::addDetection(float t_amount)
{
}

void Player::reduceDetection(float dt)
{
}

void Player::initSprites()
{
}

void Player::updateState()
{
}

void Player::updateMovement(float dt)
{
}

void Player::updateNoiseAndVisibility()
{
}

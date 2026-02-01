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
	updateMovement(dt);
	updateNoiseAndVisibility();
	reduceDetection(dt);

	m_shape.setPosition(m_Position);
}

void Player::render(sf::RenderWindow& window)
{
	// temporary logic for detection
	if (m_detectionGauge > 75.f)
	{
		m_shape.setFillColor(sf::Color::Red);
	}
	else if (m_detectionGauge > 40.f)
	{
		m_shape.setFillColor(sf::Color::Yellow);
	}
	else
	{
		m_shape.setFillColor(sf::Color(50, 50, 50));
	}
}

void Player::setPosition(sf::Vector2f t_position)
{
	m_Position = t_position;
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f();
}

void Player::addDetection(float t_amount)
{
	m_detectionGauge += t_amount;
	if (m_detectionGauge > 100.f)
	{
		m_detectionGauge = 100.f;	// stay at max!
	}
}

void Player::reduceDetection(float dt)
{
	if (m_state == PlayerState::Hiding)
	{
		m_detectionGauge -= m_detectionDecayRate * 2.f * dt;	// faster reducing gauge when hiding
	}
	else if (m_state == PlayerState::Sneaking || m_state == PlayerState::Idle)
	{
		m_detectionGauge -= m_detectionDecayRate * dt;
	}

	// no decay when walking or sprinting for now
	if (m_detectionGauge < 0.f)
	{
		m_detectionGauge = 0.f;
	}
}

void Player::initSprites()
{
	// later, maybe
}

void Player::updateState()
{
	bool isMoving = (m_Velocity.x != 0 || m_Velocity.y != 0);
	bool sneakHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl);
	bool sprintHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

	if (!isMoving)
	{
		m_state == PlayerState::Idle;
	}
	else if (sneakHeld)
	{
		m_state = PlayerState::Sneaking;
	}
	else if (sprintHeld)
	{
		m_state = PlayerState::Sprinting;
	}
	else
	{
		m_state = PlayerState::Walking;
	}
}

void Player::updateMovement(float dt)
{
	float speed = 0.f;

	switch (m_state)
	{
	case PlayerState::Sneaking:  speed = m_sneakSpeed; break;
	case PlayerState::Sprinting: speed = m_spintSpeed; break;
	case PlayerState::Walking:	 speed = m_walkSpeed;  break;
	default:					 speed = 0.f;		   break;
	}

	m_Position += m_Velocity * speed * dt;
}

void Player::updateNoiseAndVisibility()
{
	switch (m_state)
	{
		case PlayerState::Idle:
			m_noiseRadius = 0.f;
			m_visibility = 0.8f;
			break;
		case PlayerState::Sneaking:
			m_noiseRadius = 20.f;
			m_visibility = 0.4f;
			break;
		case PlayerState::Walking:
			m_noiseRadius = 80.f;
			m_visibility = 1.f;
			break;
		case PlayerState::Sprinting:
			m_noiseRadius = 200.f;
			m_visibility = 1.2f;
			break;
		case PlayerState::Hiding:
			m_noiseRadius = 0.f;
			m_visibility = 0.f;
			break;
		default:
			break;
	}
}

#pragma once

#include<iostream>
#include<SFML/Graphics.hpp>
#include"AssetManager.h"

enum class PlayerState
{
	Idle,
	Walking,
	Sneaking,
	Sprinting,
	Hiding,
	Interacting
};

class Player {

public:
	Player(AssetManager& t_assetManager);

	void handleInput();
	void update(double dt);
	void render(sf::RenderWindow& window);

	void setPosition(sf::Vector2f t_position);
	sf::Vector2f getPosition();

	// Detection system
	float getNoiseRadius() const { return m_noiseRadius; };
	float getVisibility() const { return m_visibility; };
	float getDetectionGauge() const { return m_detectionGauge; };
	void addDetection(float t_amount);
	void reduceDetection(float dt);
	bool isDetected() const { return m_detectionGauge >= 100.f; };
	bool isHiding() const { return m_state == PlayerState::Hiding; };

	PlayerState getState() const { return m_state; };

private:
	void initSprites();	// sprites to be added later, for now using shapes only
	void updateState();
	void updateMovement(float dt);
	void updateNoiseAndVisibility();

	AssetManager& m_assetManager;

	// player
	sf::RectangleShape m_temp_player;

	// movement
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	PlayerState m_state = PlayerState::Idle;

	// stats
	float m_walkSpeed = 150.0f;
	float m_sneakSpeed = 70.0f;
	float m_spintSpeed = 250.0f;		// might be removed later
	
	// stealth
	float m_noiseRadius = 0.0f;
	float m_visibility = 1.0f;
	float m_detectionGauge = 0.0f;		// you are caught when it reaches 100
	float m_detectionDecayRate = 15.0f;


};

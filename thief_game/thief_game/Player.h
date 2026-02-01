#pragma once
#include<iostream>

#include<SFML/Graphics.hpp>

class Player {

private:
	Player();

	sf::RectangleShape m_temp_player;
	float m_speed;
	float m_detection_gauge;


};

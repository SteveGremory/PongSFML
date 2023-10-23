#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball();
	Ball(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f velocity);

	auto move(const float dt, const sf::Vector2u& window_dimensions) -> void;
	auto reset(const sf::Vector2f position, const sf::Vector2f velocity)
		-> void;

	auto get_drawable() -> sf::RectangleShape&;
	auto reverse_velocity(const sf::Vector2f& player_pos) -> void;

private:
	sf::RectangleShape m_ball;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};
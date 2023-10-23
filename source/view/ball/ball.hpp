#pragma once

#include <SFML/Graphics.hpp>

enum class Direction { RIGHT, LEFT };

class Ball {
public:
	Ball();
	Ball(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f velocity);

	auto move(float dt, unsigned int window_width) -> void;
	auto reset(sf::Vector2f position, sf::Vector2f velocity) -> void;

	auto get_drawable() -> sf::RectangleShape&;
	auto reverse_velocity(Direction dir, const sf::Vector2f& player_pos)
		-> void;

private:
	sf::RectangleShape m_ball;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};
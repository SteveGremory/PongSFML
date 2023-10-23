#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
	Player(const sf::Vector2f initial_position, const float max_height);
	~Player();

	auto move(float delta_y) -> void;
	auto get_drawable() -> sf::RectangleShape&;

private:
	sf::Vector2f m_position;

	const float m_max_height;
	sf::RectangleShape m_rect_shape;
};
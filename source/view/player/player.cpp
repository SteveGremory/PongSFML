#include "player.hpp"

#include <iostream>

constexpr auto SPRITE_HEIGHT = 120.0f;
constexpr auto SPRITE_WIDTH = 10.0f;

Player::Player(const sf::Vector2f initial_position, const double max_height)
	: m_position(initial_position), m_max_height(max_height),
	  m_rect_shape(sf::Vector2f(SPRITE_WIDTH, SPRITE_HEIGHT)) {

	this->m_rect_shape.setPosition(initial_position);
}

Player::~Player() {}

auto Player::move(double delta_y) -> void {
	auto& [x, y] = m_position;
	y += delta_y;

	// Clamp it to the max height of the screen - that of the player
	y = std::clamp(y, 0.0f,
				   static_cast<float>(this->m_max_height) - SPRITE_HEIGHT);

	this->m_rect_shape.setPosition({x, y});
}

auto Player::get_drawable() -> sf::RectangleShape& {
	return this->m_rect_shape;
}
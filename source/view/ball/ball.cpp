#include "ball.hpp"
#include <iostream>

Ball::Ball() {}
Ball::Ball(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f velocity)
	: m_ball(size), m_size(m_ball.getSize()), m_position(pos),
	  m_velocity(velocity) {
	m_ball.setPosition(this->m_position);
}

auto Ball::move(double dt, const sf::Vector2f& window_dimensions) -> void {

	// move the ball
	this->m_position += this->m_velocity * static_cast<float>(dt);
	// check if outside window bounds; if so, reverse m_velocity and restore
	// at correct m_position
	if (this->m_position.y <= 0.0f) {
		this->m_velocity.y = -this->m_velocity.y;
		this->m_position.y = 0.0f;
	} else if (this->m_position.y + this->m_size.y >= window_dimensions.y) {
		this->m_velocity.y = -this->m_velocity.y;
		this->m_position.y = window_dimensions.y - this->m_size.y;
	}

	this->m_ball.setPosition(this->m_position);
}

auto Ball::reverse_velocity(const sf::Vector2f& player_pos,
							const float increment) -> void {

	// Reverse horizontal velocity
	this->m_velocity.x = -this->m_velocity.x;

	// Calculate the direction of the velocity
	int xDirection = (this->m_velocity.x < 0.0f) ? -1 : 1;
	int yDirection = (this->m_velocity.y < 0.0f) ? -1 : 1;

	// Adjust velocity with the increment value
	this->m_velocity.x += xDirection * increment;
	this->m_velocity.y += yDirection * increment;

	auto penetration = this->m_ball.getPosition().x - player_pos.x;

	// relocate
	this->m_position.x += penetration; // move ball to right

	this->m_ball.setPosition(this->m_position);
};

auto Ball::get_drawable() -> sf::RectangleShape& { return this->m_ball; }

auto Ball::reset(const sf::Vector2f position, const sf::Vector2f velocity)
	-> void {
	this->m_position = position;
	this->m_velocity = velocity;

	this->m_ball.setPosition(position);
}

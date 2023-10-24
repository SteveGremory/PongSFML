#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	/**
	 * @brief Default constructor for Ball.
	 *
	 * Constructs a Ball object with default parameters.
	 */
	Ball();

	/**
	 * @brief Constructor for Ball with custom initial parameters.
	 *
	 * Constructs a Ball object with custom position, size, and velocity.
	 *
	 * @param pos - The initial position of the ball.
	 * @param size - The size (dimensions) of the ball.
	 * @param velocity - The initial velocity of the ball.
	 */
	Ball(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f velocity);

	/**
	 * @brief Moves the ball based on the elapsed time and window dimensions.
	 *
	 * @param dt - The time elapsed since the last frame.
	 * @param window_dimensions - The dimensions of the game window.
	 */
	auto move(const float dt, const sf::Vector2u& window_dimensions) -> void;

	/**
	 * @brief Resets the ball's position and velocity.
	 *
	 * @param position - The new position for the ball.
	 * @param velocity - The new velocity for the ball.
	 */
	auto reset(const sf::Vector2f position, const sf::Vector2f velocity)
		-> void;

	/**
	 * @brief Retrieves a reference to the SFML RectangleShape representing the
	 * ball.
	 *
	 * @return A reference to an SFML RectangleShape object used for rendering
	 * the ball.
	 */
	auto get_drawable() -> sf::RectangleShape&;

	/**
	 * @brief Reverses the ball's velocity based on the player's position.
	 *
	 * This function is used to change the direction of the ball's velocity when
	 * it collides with a player, taking the player's position into account.
	 *
	 * @param player_pos - The position of the player with which the ball
	 * collides.
	 */
	auto reverse_velocity(const sf::Vector2f& player_pos) -> void;

private:
	sf::RectangleShape m_ball;

	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};
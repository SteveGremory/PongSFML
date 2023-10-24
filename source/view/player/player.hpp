#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
	/**
	 * @brief Constructs a Player object with the initial position and maximum
	 * height.
	 *
	 * @param initial_position - The initial position of the player character.
	 * @param max_height - The maximum height the player can reach in the game.
	 */
	Player(const sf::Vector2f initial_position, const float max_height);

	/**
	 * @brief Destroys the Player object.
	 *
	 * This is the destructor for the Player class.
	 */
	~Player();

	/**
	 * @brief Moves the player character by a specified vertical distance.
	 *
	 * @param delta_y - The vertical distance by which the player should be
	 * moved.
	 */
	auto move(float delta_y) -> void;

	/**
	 * @brief Returns a reference to the SFML RectangleShape representing the
	 * player character.
	 *
	 * @return A reference to an SFML RectangleShape object used for rendering
	 * the player.
	 */
	auto get_drawable() -> sf::RectangleShape&;

private:
	sf::Vector2f m_position;

	const float m_max_height;
	sf::RectangleShape m_rect_shape;
};
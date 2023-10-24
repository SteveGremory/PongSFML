#pragma once

#include <SFML/Graphics.hpp>
#include <array>

class GameState {
public:
	/**
	 * @brief Default constructor for GameState.
	 *
	 * Constructs a GameState object with default parameters.
	 */
	GameState() = default;

	/**
	 * @brief Virtual destructor for GameState.
	 *
	 * This is the virtual destructor for the GameState class, ensuring that
	 * derived classes can manage their resources properly when destroyed.
	 */
	virtual ~GameState() = default;

	/**
	 * @brief Tick the current game state.
	 *
	 * This pure virtual function is used to update the current game state.
	 * Derived classes must implement this function to perform state-specific
	 * logic.
	 *
	 * @param dt - The time elapsed since the last frame.
	 * @param window - A reference to the SFML RenderWindow used for rendering.
	 * @return true if the game state should continue; otherwise, false to exit
	 * the game.
	 */
	virtual auto tick(const double& dt, sf::RenderWindow& window) -> bool = 0;

	/**
	 * @brief Checks if the game state should exit the game.
	 *
	 * This function is used to determine whether the current game state should
	 * trigger an exit from the game.
	 *
	 * @return true if the game state should exit the game; otherwise, false.
	 */
	inline auto should_exit_game() -> bool { return this->should_exit; };

protected:
	bool should_exit{false}; // A flag indicating if the game state should
							 // trigger an exit.
};

/**
 * @brief The Game class is responsible for maintaining the global state of the
 * program.
 *
 * The Game class is the central component of the program, responsible for
 * managing game states, rendering, and executing the game loop.
 */
class Game {
public:
	/**
	 * @brief Constructs a Game object with a vector of game states.
	 *
	 * @param states - A vector of unique pointers to GameState objects
	 * representing different game states.
	 * @param dimensions - The dimensions of the window to be constructed.
	 */
	Game(std::vector<std::unique_ptr<GameState>>& states,
		 const sf::Vector2u& dimensions);

	/**
	 * @brief Destroys the Game object.
	 *
	 * This is the destructor for the Game class.
	 */
	~Game();

	/**
	 * @brief Executes the game loop, handling game state transitions and
	 * rendering.
	 *
	 * The game loop is responsible for updating the game, transitioning between
	 * different game states, and rendering the current game state.
	 */
	auto game_loop() -> void;

private:
	size_t m_current_state_idx;
	std::vector<std::unique_ptr<GameState>> m_states;
	sf::RenderWindow m_window;
};
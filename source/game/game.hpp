#pragma once

#include <SFML/Graphics.hpp>
#include <array>

constexpr sf::Vector2u DIMENSIONS{1280, 720};

class GameState {
public:
	GameState() = default;
	virtual ~GameState() = default;

	/**
	 * @brief Tick the current game state
	 *
	 */
	virtual auto tick(float dt, sf::RenderWindow& window) -> bool = 0;
	inline auto should_exit_game() -> bool { return this->should_exit; };

protected:
	bool should_exit;
};

/**
 * @brief: The game class is responsible for maintaining the global state of the
 * program.
 */
class Game {
public:
	Game(std::vector<std::unique_ptr<GameState>>& states);
	~Game();

	auto game_loop() -> void;

private:
	size_t m_current_state_idx;

	std::vector<std::unique_ptr<GameState>> m_states;
	sf::RenderWindow m_window;
};
#include "game/game.hpp"
#include "utils/timer.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>

/**
 * @brief: The game class is responsible for maintaining the global state of the
 * program.
 */

Game::Game(std::vector<std::unique_ptr<GameState>>& states)
	: m_current_state_idx(0), m_states(std::move(states)),
	  m_window(sf::RenderWindow(sf::VideoMode(DIMENSIONS), "Pong")) {
	this->m_window.setVerticalSyncEnabled(true);
}
Game::~Game() {}

auto Game::game_loop() -> void {

	double delta_time = 0.0f;

	utils::Timer timer{};

	sf::Texture texture;
	if (!texture.loadFromFile(
			std::filesystem::path("../assets/background.jpg"))) {
		throw std::filesystem::filesystem_error(
			"Could not load in the background.", std::error_code());
	}
	sf::Sprite sprite{texture};
	sf::Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(sprite.getTexture().getSize() / 2u));
	sprite.setPosition(this->m_window.getView().getCenter());

	while (this->m_window.isOpen()) {
		// clear the window with black color
		this->m_window.clear(sf::Color::Black);
		this->m_window.draw(sprite);

		auto& current_state = this->m_states[this->m_current_state_idx];

		delta_time = timer.elapsed_time();
		timer.reset();

		if (!current_state->tick(delta_time, this->m_window)) {

			if (current_state->should_exit_game()) {
				this->m_window.close();
			}

			m_current_state_idx = (m_current_state_idx + 1) % m_states.size();
		}

		// end the current frame
		this->m_window.display();
	}
}

#include "pongstate.hpp"

constexpr auto PLAYER_SPEED = 1000.0f;

PongState::PongState(sf::Font& font)
	: m_player_one({DIMENSIONS.x * 0.05f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  m_player_two({DIMENSIONS.x * 0.95f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  p1_score(0), p2_score(0),
	  p1_score_label("0", font, Pong::FontSize::FONT_BIG),
	  p2_score_label("0", font, Pong::FontSize::FONT_BIG) {
	p1_score_label.set_position({DIMENSIONS.x * 0.2f, DIMENSIONS.x * 0.1f});
	p2_score_label.set_position({DIMENSIONS.x * 0.8f, DIMENSIONS.x * 0.1f});
}

auto PongState::tick(const float dt, sf::RenderWindow& window) -> bool {

	sf::Event event;
	while (window.pollEvent(event)) {
		// If the close button was pressed
		// then close the window
		switch (event.type) {

		case sf::Event::KeyPressed: {
			switch (event.key.scancode) {

			case sf::Keyboard::Scan::Backspace:
				p1_score++;
				p2_score++;

				p1_score_label.set_text(std::to_string(p1_score));
				p2_score_label.set_text(std::to_string(p2_score));

				break;

			case sf::Keyboard::Scan::Escape:
				this->should_exit = true;
				return false;

				break;

			default:
				break;
			}

			break;
		}

		case sf::Event::Closed:
			// Set should_exit to true so that
			// the state knows that we must close the window
			this->should_exit = true;
			return false;

			break;

		default:
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->m_player_one.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_player_one.move(PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->m_player_two.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->m_player_two.move(PLAYER_SPEED * dt);
	}

	window.draw(this->m_player_one.get_drawable());
	window.draw(this->m_player_two.get_drawable());

	window.draw(this->p1_score_label.get_sfml_text());
	window.draw(this->p2_score_label.get_sfml_text());

	return true;
}

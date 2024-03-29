#include "menustate.hpp"
#include "utils/io.hpp"

#include <iostream>

MenuState::MenuState(const sf::Font& font, const sf::Vector2u& dimensions)
	: m_menu(font, dimensions), startup_sound(this->sound_buffer) {

	utils::load_sound(this->sound_buffer, "./assets/game_start.mp3");
}

auto MenuState::tick(const double&, sf::RenderWindow& window) -> bool {

	sf::Event event;
	while (window.pollEvent(event)) {
		// If the close button was pressed
		// then close the window
		switch (event.type) {

		case sf::Event::KeyPressed: {
			switch (event.key.scancode) {

			case sf::Keyboard::Scan::Down:
				this->m_menu.change_selection();
				break;
			case sf::Keyboard::Scan::Up:
				this->m_menu.change_selection();
				break;

			case sf::Keyboard::Scan::Enter:
				if (this->m_menu.is_start_selected()) {
					this->startup_sound.play();
					return false;
				} else {
					this->should_exit = true;
					return false;
				}

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

		default:
			break;
		}
	}

	for (auto& item : this->m_menu.get_items()) {
		window.draw(item.get_sfml_text());
	}

	return true;
}

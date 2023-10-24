#include "menu.hpp"
#include "utils/io.hpp"

namespace Pong {

Menu::Menu(const sf::Font& font, const sf::Vector2u dimensions)
	: m_items{
		  Text{"Welcome to PONG!", font, FontSize::FONT_BIG},
		  Text{"> Start", font, FontSize::FONT_MEDIUM},
		  Text{"Exit", font, FontSize::FONT_MEDIUM},
	  }, btn_sound(this->btn_sound_buffer) {

	auto& [title, start, exit] = m_items;

	title.set_position({dimensions.x * 0.5f, dimensions.y * 0.2f});
	start.set_position({dimensions.x * 0.5f, dimensions.y * 0.5f});
	exit.set_position({dimensions.x * 0.5f, dimensions.y * 0.6f});

	utils::load_sound(this->btn_sound_buffer, "./assets/button_select.mp3");
	btn_sound.setVolume(40);
}

auto Menu::get_items() -> std::span<Text, 3> { return this->m_items; }
auto Menu::is_start_selected() -> bool { return this->start_selected; }

auto Menu::change_selection() -> bool {
	start_selected = !start_selected;
	auto& [_, start, exit] = m_items;

	if (start_selected) {
		// Select the start button
		start.set_text("> Start");
		exit.set_text("Exit");
	} else {
		// Select the exit button
		start.set_text("Start");
		exit.set_text("> Exit");
	}

	this->btn_sound.play();

	return start_selected;
}

} // namespace Pong

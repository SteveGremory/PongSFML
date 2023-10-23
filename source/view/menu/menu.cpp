#include "menu.hpp"

namespace Pong {

Menu::Menu(const sf::Font& font, const sf::Vector2u dimensions)
	: m_items{
		  Text{"Welcome to PONG!", font, FontSize::FONT_BIG},
		  Text{"> Start", font, FontSize::FONT_MEDIUM},
		  Text{"Exit", font, FontSize::FONT_MEDIUM},
	  } {

	auto& [title, start, exit] = m_items;

	title.set_position({dimensions.x * 0.5f, dimensions.y * 0.2f});
	start.set_position({dimensions.x * 0.5f, dimensions.y * 0.4f});
	exit.set_position({dimensions.x * 0.5f, dimensions.y * 0.5f});
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

	return start_selected;
}

} // namespace Pong

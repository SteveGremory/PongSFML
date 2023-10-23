#pragma once

#include "view/text/text.hpp"
#include <span>

namespace Pong {

class Menu {
public:
	Menu(const sf::Font& font, const sf::Vector2u dimensions);

	auto get_items() -> std::span<Text, 3>;
	auto is_start_selected() -> bool;

	auto change_selection() -> bool;

private:
	std::array<Text, 3> m_items;
	bool start_selected{true};
};

} // namespace Pong

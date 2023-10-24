#pragma once

#include "view/text/text.hpp"
#include <span>

#include <SFML/Audio.hpp>

namespace Pong {

class Menu {
public:
	/**
	 * @brief Constructs a Menu object with the given font and dimensions.
	 *
	 * @param font - The SFML font used for rendering text items.
	 * @param dimensions - The dimensions (width and height) of the menu.
	 */
	Menu(const sf::Font& font, const sf::Vector2u dimensions);

	/**
	 * @brief Returns a span of Text items that make up the menu.
	 *
	 * @return A std::span containing Text items representing the menu's text
	 * items.
	 */
	auto get_items() -> std::span<Text, 3>;

	/**
	 * @brief Checks if the "Start" item is currently selected in the menu.
	 *
	 * @return true if the "Start" item is selected; otherwise, false.
	 */
	auto is_start_selected() -> bool;

	/**
	 * @brief Changes the selection within the menu.
	 *
	 * This function allows the user to change the currently selected item in
	 * the menu.
	 *
	 * @return true if the selection changed; otherwise, false.
	 */
	auto change_selection() -> bool;

private:
	std::array<Text, 3> m_items;
	bool start_selected{true};

	sf::SoundBuffer btn_sound_buffer;
	sf::Sound btn_sound;
};

} // namespace Pong

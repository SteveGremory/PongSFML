#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>

#include <string_view>

namespace Pong {

namespace FontSize {
enum : unsigned int {
	FONT_BIG = 64,
	FONT_MEDIUM = 32,
	FONT_SMALL = 24,
};
}

class Text {
public:
	/**
	 * @brief Constructs a Player object with the initial position and maximum
	 * height.
	 *
	 * @param initial_text - The initial text.
	 * @param font - The font to be used for the text.
	 * @param font_size - The size of the font.
	 */
	Text(const std::string_view initial_text, const sf::Font& font,
		 unsigned int font_size);

	/**
	 * @brief A Default destructor for the Text class.
	 */
	~Text() = default;

	/**
	 * @brief Centers the text anchor.
	 *
	 * This function is used to set the anchor point of the text to its center.
	 * When rendering the text, it will be centered around its position.
	 */
	auto center_text_anchor() -> void;

	/**
	 * @brief Sets the text content to a new string.
	 *
	 * @param new_text - The new text content to be displayed.
	 */
	auto set_text(const std::string_view new_text) -> void;

	/**
	 * @brief Sets the position of the text.
	 *
	 * @param position - The position where the text should be displayed.
	 */
	auto set_position(const sf::Vector2f& position) -> void;

	/**
	 * @brief Retrieves the SFML Text object.
	 *
	 * This function returns the SFML Text object that represents the text
	 * along with its properties, such as font, size, style, and color.
	 *
	 * @return An SFML Text object.
	 */
	auto get_sfml_text() const -> sf::Text;

	/**
	 * @brief Retrieves the current position of the text.
	 *
	 * @return A constant reference to an SFML Vector2f representing the
	 * position of the text.
	 */
	auto get_position() const -> sf::Vector2f;

private:
	sf::Text m_text;
	sf::Vector2f m_position;
	sf::FloatRect m_text_rect;
};

} // namespace Pong

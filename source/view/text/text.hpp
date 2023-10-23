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
	Text(const std::string_view initial_text, const sf::Font& font,
		 unsigned int font_size);

	auto center_text_anchor() -> void;
	auto set_text(const std::string_view new_text) -> void;
	auto set_position(const sf::Vector2f& position) -> void;

	auto get_sfml_text() const -> sf::Text;
	auto get_position() const -> sf::Vector2f;

private:
	sf::Text m_text;
	sf::Vector2f m_position;
	sf::FloatRect m_text_rect;
};

} // namespace Pong

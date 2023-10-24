#pragma once

#include <SFML/Graphics.hpp>

namespace utils {
auto check_collision(sf::RectangleShape& one, sf::RectangleShape& two) -> bool {
	// collision x-axis?
	bool collision_x =
		one.getPosition().x + one.getSize().x >= two.getPosition().x &&
		two.getPosition().x + two.getSize().x >= one.getPosition().x;
	// collision y-axis?
	bool collision_y =
		one.getPosition().y + one.getSize().y >= two.getPosition().y &&
		two.getPosition().y + two.getSize().y >= one.getPosition().y;

	// collision only if on both axes
	return collision_x && collision_y;
}
} // namespace utils

#include "game/states/menustate.hpp"
#include "game/states/pongstate.hpp"

#include "game/game.hpp"

#include <iostream>
#include <memory>
#include <span>

auto main() -> int {

	// Hardcoded path to the font
	const std::filesystem::path font_path("../assets/PressStart2P-Regular.ttf");
	// Initialise the font to be used
	sf::Font font{};
	if (!font.loadFromFile(font_path)) {
		throw std::runtime_error("Failed to load the font");
	}

	std::vector<std::unique_ptr<GameState>> states;

	states.emplace_back(std::make_unique<MenuState>(font, DIMENSIONS));
	states.emplace_back(std::make_unique<PongState>(font));

	Game game(states);

	game.game_loop();

	return 0;
}
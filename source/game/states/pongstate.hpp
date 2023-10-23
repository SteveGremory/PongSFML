#pragma once

#include "game/game.hpp"

class PongState : public GameState {
public:
	PongState() = default;
	~PongState() = default;

	auto tick(float dt, sf::RenderWindow& window) -> bool final;
};

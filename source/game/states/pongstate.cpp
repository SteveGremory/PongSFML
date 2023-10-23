#include "pongstate.hpp"

constexpr auto PLAYER_SPEED = 1000.0f;
constexpr auto BALL_SPEED = 200.0f;

PongState::PongState(sf::Font& font)
	: m_player_one({DIMENSIONS.x * 0.05f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  m_player_two({DIMENSIONS.x * 0.95f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  m_p1_score(0), m_p2_score(0),
	  m_p1_score_label("0", font, Pong::FontSize::FONT_BIG),
	  m_p2_score_label("0", font, Pong::FontSize::FONT_BIG),
	  m_ball({DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.5f}, {20, 20},
			 {BALL_SPEED, BALL_SPEED}) {
	this->m_p1_score_label.set_position(
		{DIMENSIONS.x * 0.2f, DIMENSIONS.x * 0.1f});
	this->m_p2_score_label.set_position(
		{DIMENSIONS.x * 0.8f, DIMENSIONS.x * 0.1f});
}

auto PongState::check_collision(sf::RectangleShape& one,
								sf::RectangleShape& two) -> bool {
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

auto PongState::tick(const float dt, sf::RenderWindow& window) -> bool {

	sf::Event event;
	while (window.pollEvent(event)) {
		// If the close button was pressed
		// then close the window
		switch (event.type) {

		case sf::Event::KeyPressed: {
			switch (event.key.scancode) {

			case sf::Keyboard::Scan::Backspace:
				this->m_p1_score++;
				this->m_p2_score++;

				this->m_p1_score_label.set_text(
					std::to_string(this->m_p1_score));
				this->m_p2_score_label.set_text(
					std::to_string(this->m_p2_score));

				break;

			case sf::Keyboard::Scan::Escape:
				this->should_exit = true;
				return false;

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

			break;

		default:
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		this->m_player_one.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		this->m_player_one.move(PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->m_player_two.move(-PLAYER_SPEED * dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->m_player_two.move(PLAYER_SPEED * dt);
	}

	window.draw(this->m_ball.get_drawable());

	if (this->check_collision(this->m_ball.get_drawable(),
							  this->m_player_one.get_drawable())) {
		// Left collision
		m_ball.reverse_velocity(
			Direction::LEFT, this->m_player_one.get_drawable().getPosition());
		std::cout << "CRASH WITH THE LEFT BAT" << std::endl;
	} else {
		m_ball.move(dt, DIMENSIONS.y);
	}
	if (this->check_collision(this->m_ball.get_drawable(),
							  this->m_player_two.get_drawable())) {
		// Right collision
		m_ball.reverse_velocity(
			Direction::RIGHT, this->m_player_two.get_drawable().getPosition());
		std::cout << "CRASH WITH THE RIGHT BAT" << std::endl;
	} else {
		m_ball.move(dt, DIMENSIONS.y);
	}

	window.draw(this->m_player_one.get_drawable());
	window.draw(this->m_player_two.get_drawable());

	window.draw(this->m_p1_score_label.get_sfml_text());
	window.draw(this->m_p2_score_label.get_sfml_text());

	return true;
}

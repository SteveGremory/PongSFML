#include "pongstate.hpp"

constexpr auto PLAYER_SPEED = 1000.0f;
constexpr auto BALL_SPEED = 300.0f;

PongState::PongState(sf::Font& font)
	: m_player_one({DIMENSIONS.x * 0.05f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  m_player_two({DIMENSIONS.x * 0.95f, DIMENSIONS.y * 0.5f}, DIMENSIONS.y),
	  m_p1_score(0), m_p2_score(0),
	  m_p1_score_label("0", font, Pong::FontSize::FONT_BIG),
	  m_p2_score_label("0", font, Pong::FontSize::FONT_BIG),

	  m_game_over_label("Game over!", font, Pong::FontSize::FONT_BIG),
	  m_winner_label("0", font, Pong::FontSize::FONT_MEDIUM),
	  m_ball({DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.5f}, {20, 20},
			 {BALL_SPEED, BALL_SPEED}) {

	this->m_p1_score_label.set_position(
		{DIMENSIONS.x * 0.2f, DIMENSIONS.x * 0.1f});
	this->m_p2_score_label.set_position(
		{DIMENSIONS.x * 0.8f, DIMENSIONS.x * 0.1f});

	this->m_game_over_label.set_position(
		{DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.6f});
	this->m_winner_label.set_position(
		{DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.4f});
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

	if (this->m_rounds == 5) {
		int pt_diff = 0;

		// The game has ended
		if (this->m_p1_score > this->m_p2_score) {
			pt_diff = this->m_p1_score - this->m_p2_score;
			this->m_winner_label.set_text("P1 Wins by " +
										  std::to_string(pt_diff) + " points.");
		} else {
			pt_diff = this->m_p2_score - this->m_p1_score;
			this->m_winner_label.set_text("P2 Wins!" + std::to_string(pt_diff) +
										  " points.");
		}

		window.draw(this->m_game_over_label.get_sfml_text());
		window.draw(this->m_winner_label.get_sfml_text());

		this->m_p1_score = 0;
		this->m_p2_score = 0;

		this->m_p1_score_label.set_text(std::to_string(this->m_p1_score));
		this->m_p2_score_label.set_text(std::to_string(this->m_p2_score));

		this->m_rounds = 0;

		window.display();

		sf::sleep(sf::seconds(5.0f));

		return false;
	}

	sf::Event event;
	while (window.pollEvent(event)) {
		// If the close button was pressed
		// then close the window
		switch (event.type) {

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

	if (this->check_collision(this->m_ball.get_drawable(),
							  this->m_player_one.get_drawable())) {
		// Left collision
		m_ball.reverse_velocity(
			this->m_player_one.get_drawable().getPosition());
	}

	if (this->check_collision(this->m_ball.get_drawable(),
							  this->m_player_two.get_drawable())) {
		// Right collision
		m_ball.reverse_velocity(
			this->m_player_two.get_drawable().getPosition());
	}

	m_ball.move(dt, DIMENSIONS);

	if (m_ball.get_drawable().getPosition().x <= 0.0f) {
		m_p2_score++;
		this->m_rounds++;
		this->m_p2_score_label.set_text(std::to_string(this->m_p2_score));

		this->m_ball.reset({DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.5f},
						   {BALL_SPEED, BALL_SPEED});

	} else if (m_ball.get_drawable().getPosition().x +
				   m_ball.get_drawable().getSize().x >=
			   window.getSize().x) {

		m_p1_score++;
		this->m_rounds++;

		this->m_p1_score_label.set_text(std::to_string(this->m_p1_score));
		this->m_ball.reset({DIMENSIONS.x * 0.5f, DIMENSIONS.y * 0.5f},
						   {BALL_SPEED, BALL_SPEED});
	}

	window.draw(this->m_ball.get_drawable());

	window.draw(this->m_player_one.get_drawable());
	window.draw(this->m_player_two.get_drawable());

	window.draw(this->m_p1_score_label.get_sfml_text());
	window.draw(this->m_p2_score_label.get_sfml_text());

	return true;
}

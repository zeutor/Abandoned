#include "Application.hpp"
#include "SFML/Graphics.hpp"
#include "Outdata.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "MapManager.hpp"


void Application::INIT() {
	_window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Abandoned");
	_window->setFramerateLimit(FRAME_LIMIT);
}

void Application::RUN() {
	outdata::getFiles();

	Player* player = new Player(outdata::player_texture, sf::Vector2f(0, 0), *_window);

	sf::Text text("", outdata::mainFont, 20);

	sf::Clock deltaClock;
	sf::Clock gameClock;
	while (_window->isOpen()) {
		float deltaTime = deltaClock.getElapsedTime().asSeconds();
		deltaClock.restart();

		deltaTime *= TIME_MULTIPLIER;

		sf::Event event;
		while (_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window->close();
		}

		text.setString(std::to_string(player->_distance / PIXELS_PER_METER));

		player->Update(deltaTime);

		_window->clear(sf::Color::Black);

		mapManager::drawMap(*_window);
		_window->draw(player->getSprite());
		_window->draw(text);
		_window->display();
	}
}

void Application::CLOSE() {
	if (!_window)
		delete _window;
}
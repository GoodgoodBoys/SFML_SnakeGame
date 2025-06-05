#include "game.hpp"
#include "map.hpp"
#include "snake.hpp"
#include "food.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace snakeGame;

Game::Game(unsigned int width, unsigned int length, sf::Color background, std::string title)
	: width(width)
	, length(length)
	, background(background)
	, title(title)
	, newDirection(Direction::up)
{}

void Game::run() {
	sf::RenderWindow window(sf::VideoMode({this->width, this->length}), this->title);

	sf::Font font;
	if (!font.openFromFile("resource/fonts/times.ttf")) {
		return;  // ◊÷ÃÂº”‘ÿ ß∞‹
	}
	sf::Text text(font);
	text.setString("You lost");
	text.setCharacterSize(36);
	text.setFillColor(sf::Color::White);
	text.setPosition({ 100.f, 100.f });

	std::array<int, 100> mapDist = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	Map map(50, mapDist);
	map.update();

	Snake snake(2, 3, 3, 50.f, Direction::up);

	sf::Clock clock;
	sf::Time interval = sf::seconds(0.5f);

	Food food(50.f);
	food.update(snake.getBody(), map.getMap(), "wolien");

	SnakeStatus snakeStatus;

	newDirection = snake.getDirection();

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::KeyPressed>())
				setSnakeDirection(event->getIf<sf::Event::KeyPressed>()->code, snake);

			if (event->is<sf::Event::Closed>())
				window.close();
		}

		if (clock.getElapsedTime() >= interval && !snake.isDead()) {
			snake.setDirection(newDirection);
			snake.move(false);
			snakeStatus = snakeEventDetection(snake, map, food);
			if (snakeStatus == SnakeStatus::eat) {
				snake.move(true);
				food.update(snake.getBodyNew(), map.getMap(), "wolien");
				snake.update();
			}
			else if (snakeStatus == SnakeStatus::knockSelf || snakeStatus == SnakeStatus::knockWall) {
				snake.dead();
			} else
				snake.update();

			clock.restart();
		}

		window.clear();
		if (!snake.isDead()) {
			map.draw(window);
			food.draw(window);
			snake.draw(window);
		}
		else
			window.draw(text);

		window.display();
	}
}

void Game::setSnakeDirection(sf::Keyboard::Key key, Snake& snake) {
	if (key == sf::Keyboard::Key::W)
		newDirection = Direction::up;
	else if (key == sf::Keyboard::Key::S)
		newDirection = Direction::down;
	else if (key == sf::Keyboard::Key::A)
		newDirection = Direction::left;
	else if (key == sf::Keyboard::Key::D)
		newDirection = Direction::right;
}

SnakeStatus Game::snakeEventDetection(Snake snake, Map map, Food food) {
	if (snake.getHeadNew() == food.getPosition())
		return SnakeStatus::eat;
	if (map.getMap().at(snake.getHeadNew().first + snake.getHeadNew().second * 10) == 1)
		return SnakeStatus::knockWall;
	if (snake.isHitSelf())
		return SnakeStatus::knockSelf;
	return normal;
}

Game::~Game() {
}
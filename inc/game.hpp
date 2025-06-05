#ifndef SNAKEGAME
#define SNAKEGAME

#include <SFML/Graphics.hpp>
#include "snake.hpp"
#include "map.hpp"
#include "food.hpp"

namespace snakeGame {

enum SnakeStatus {normal, eat, knockWall, knockSelf};

class Game {
private:
	unsigned int width, length;
	sf::Color background;
	std::string title;
	Direction newDirection;

public:
	Game(unsigned int width, unsigned int length, sf::Color gackground, std::string title);
	~Game();
	void run();
	void setSnakeDirection(sf::Keyboard::Key key, Snake& snake);
	SnakeStatus snakeEventDetection(Snake snake, Map map, Food food);
};
}

#endif // SNAKEGAME

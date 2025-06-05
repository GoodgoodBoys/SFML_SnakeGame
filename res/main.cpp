#include "game.hpp"

int main()
{
	snakeGame::Game game(500, 500, sf::Color::Black, "My Snake Game Demo");
	game.run();

	return 0;
}
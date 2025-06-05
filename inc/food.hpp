#ifndef FOOD
#define FOOD

#include <SFML/Graphics.hpp>
#include <string>

namespace snakeGame {

class Food {
private:
	std::pair<int, int> food;
	sf::VertexArray va_food;
	sf::Texture     m_tileset;
	float unitSize;

public:
	Food(float unit, std::string texturePath = "resource/img/wolien.jpg");
	~Food();
	std::pair<int, int> getPosition();
	std::pair<int, int> newPosition(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map);
	void update(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map);
	void update(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map, std::string foodName);
	void draw(sf::RenderTarget& target);
};

}

#endif // FOOD
#ifndef MAP
#define MAP

#include <SFML/Graphics.hpp>
#include <array>

namespace snakeGame {

class Map {
private:
	unsigned int blockWidth;
	std::array<int, 100> map;

	sf::VertexArray va_map;

public:
	Map(unsigned int width, std::array<int, 100> map);
	~Map();
	std::array<int, 100> getMap();
	void update();
	void draw(sf::RenderTarget& target);

};

}

#endif // MAP
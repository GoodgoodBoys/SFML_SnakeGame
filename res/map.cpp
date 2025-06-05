#include "map.hpp"

using namespace snakeGame;

Map::Map(unsigned int width, std::array<int, 100> map)
: blockWidth(width)
, map(map)
{
	va_map.setPrimitiveType(sf::PrimitiveType::Triangles);
	va_map.resize(100 * 6);
}

Map::~Map() {}

std::array<int, 100> Map::getMap() {
	return map;
}

void Map::update() {
	for (unsigned int i = 0; i < 10; i++) {
		for (unsigned int j = 0; j < 10; j++) {
			if(map[i * 10 + j] == 1) {
				va_map[(i * 10 + j) * 6 + 0].position = sf::Vector2f({ static_cast<float>(i * blockWidth), static_cast<float>(j * blockWidth) });
				va_map[(i * 10 + j) * 6 + 1].position = sf::Vector2f({ static_cast<float>(i * blockWidth + blockWidth), static_cast<float>(j * blockWidth) });
				va_map[(i * 10 + j) * 6 + 2].position = sf::Vector2f({ static_cast<float>(i * blockWidth + blockWidth), static_cast<float>(j * blockWidth + blockWidth) });
				va_map[(i * 10 + j) * 6 + 3].position = sf::Vector2f({ static_cast<float>(i * blockWidth), static_cast<float>(j * blockWidth) });
				va_map[(i * 10 + j) * 6 + 4].position = sf::Vector2f({ static_cast<float>(i * blockWidth), static_cast<float>(j * blockWidth + blockWidth) });
				va_map[(i * 10 + j) * 6 + 5].position = sf::Vector2f({ static_cast<float>(i * blockWidth + blockWidth), static_cast<float>(j * blockWidth + blockWidth) });

				va_map[(i * 10 + j) * 6 + 0].color = sf::Color::Red;
				va_map[(i * 10 + j) * 6 + 1].color = sf::Color::Red;
				va_map[(i * 10 + j) * 6 + 2].color = sf::Color::Red;
				va_map[(i * 10 + j) * 6 + 3].color = sf::Color::Red;
				va_map[(i * 10 + j) * 6 + 4].color = sf::Color::Red;
				va_map[(i * 10 + j) * 6 + 5].color = sf::Color::Red;
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target) {
	target.draw(va_map);
}

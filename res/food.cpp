#include "food.hpp"

#include <random>
#include <iostream>

using namespace snakeGame;

Food::Food(float unit, std::string texturePath): unitSize(unit) {
	va_food.setPrimitiveType(sf::PrimitiveType::Triangles);
	va_food.resize(6);

	if(!m_tileset.loadFromFile(texturePath))
		return;
}

Food::~Food() {

}

std::pair<int, int> Food::getPosition() {
	return food;
}

std::pair<int, int> Food::newPosition(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map) {
	std::pair<int, int> targetPosition;

	for (int i = 0; i < snakeBody.size() - 1; i++) {
		map.at(snakeBody.at(i).first + snakeBody.at(i).second * 10) = 1;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 9);

	do
	{
		targetPosition.first = distrib(gen);
		targetPosition.second = distrib(gen);
	} while (1 == map.at(targetPosition.first + targetPosition.second * 10));

	std::cout << "targetPosition = " << targetPosition.first << targetPosition.second  << std::endl;
	food = targetPosition;
	return targetPosition;
}
void Food::update(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map) {
	std::pair<int, int> targetPosition = newPosition(snakeBody, map);

	va_food[0].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize) });
	va_food[1].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize) });
	va_food[2].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });
	va_food[3].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize) });
	va_food[4].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });
	va_food[5].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });

	va_food[0].color = sf::Color::Green;
	va_food[1].color = sf::Color::Green;
	va_food[2].color = sf::Color::Green;
	va_food[3].color = sf::Color::Green;
	va_food[4].color = sf::Color::Green;
	va_food[5].color = sf::Color::Green;
}

void Food::update(std::vector<std::pair<int, int>> snakeBody, std::array<int, 100> map, std::string foodName) {
	if (foodName == "wolien") {
		std::pair<int, int> targetPosition = newPosition(snakeBody, map);

		va_food[0].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize) });
		va_food[1].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize) });
		va_food[2].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });
		va_food[3].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize) });
		va_food[4].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });
		va_food[5].position = sf::Vector2f({ static_cast<float>(targetPosition.first * unitSize + unitSize), static_cast<float>(targetPosition.second * unitSize + unitSize) });

		
		va_food[0].texCoords = sf::Vector2f( {0.f, 0.f} );
		va_food[1].texCoords = sf::Vector2f( { 0.f + unitSize, 0.f });
		va_food[2].texCoords = sf::Vector2f({ 0.f + unitSize, 0.f + unitSize });
		va_food[3].texCoords = sf::Vector2f({ 0.f, 0.f });
		va_food[4].texCoords = sf::Vector2f({ 0.f, 0.f + unitSize });
		va_food[5].texCoords = sf::Vector2f({ 0.f + unitSize, 0.f + unitSize });
	}

}

void Food::draw(sf::RenderTarget& target) {
	sf::RenderStates states;
	states.texture = &m_tileset;
	target.draw(va_food, states);
}


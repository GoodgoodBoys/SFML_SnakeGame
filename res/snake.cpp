#include "snake.hpp"

#include <iostream>

using namespace snakeGame;

Snake::Snake(int initalLength, int initalPositionX, int initalPositionY, float unitsize, Direction initialDirection)
{
	bodyLength = 0;
	unitSize = unitsize;
	movingDirection = initialDirection;
	alive = true;

	body.push_back( std::make_pair(initalPositionX, initalPositionY) );

	while (body.size() < initalLength) {
		body.push_back( std::make_pair(body.at(bodyLength).first, body.at(bodyLength).second + 1) );
		bodyLength++;
	}
	va_body.setPrimitiveType(sf::PrimitiveType::Triangles);
	bodyNew = body;
	update();
}

Snake::~Snake() {}

void Snake::dead() {
	alive = false;
}

bool Snake::isDead() {
	return !alive;
}

bool Snake::isHitSelf() {
	for (int i = 1; i < body.size() - 1; i++) {
		if (this->getHeadNew() == bodyNew.at(i)) {
			return true;
		}		
	}
	return false;
}

std::pair<int, int> Snake::getHead() {
	return body.at(0);
}

std::pair<int, int> Snake::getHeadNew() {
	return bodyNew.at(0);
}


Direction Snake::getDirection() {
	return movingDirection;
}

void Snake::setDirection(Direction target) {
	if (movingDirection == Direction::up && target != Direction::down ||
		movingDirection == Direction::left && target != Direction::right ||
		movingDirection == Direction::down && target != Direction::up ||
		movingDirection == Direction::right && target != Direction::left
		)
		movingDirection = target;
}

std::vector<std::pair<int, int>> Snake::getBody() {
	return body;
}

std::vector<std::pair<int, int>> Snake::getBodyNew() {
	return bodyNew;
}

void Snake::move(bool prolong) {
	bodyNew = body;
	if (prolong)
		bodyNew.push_back(std::make_pair(bodyNew.at(bodyNew.size() - 1).first, bodyNew.at(bodyNew.size() - 1).second));

	for (int i = static_cast<int>(bodyNew.size() - 1); i > 0; i--) {
		bodyNew.at(i) = bodyNew.at(i - 1);
	}

	switch (movingDirection) {
		case Direction::up:
			bodyNew.at(0).second--;
			break;
		case Direction::left:
			bodyNew.at(0).first--;
			break;
		case Direction::down:
			bodyNew.at(0).second++;
			break;
		case Direction::right:
			bodyNew.at(0).first++;
			break;
	}
}

void Snake::update() {
	body = bodyNew;
	va_body.resize(body.size() * 6);
	for (int i = 0; i < body.size(); i++) {
		va_body[i * 6 + 0].position = sf::Vector2f({ body.at(i).first * unitSize, body.at(i).second * unitSize });
		va_body[i * 6 + 1].position = sf::Vector2f({ body.at(i).first * unitSize + unitSize, body.at(i).second * unitSize });
		va_body[i * 6 + 2].position = sf::Vector2f({ body.at(i).first * unitSize + unitSize, body.at(i).second * unitSize + unitSize });
		va_body[i * 6 + 3].position = sf::Vector2f({ body.at(i).first * unitSize, body.at(i).second * unitSize });
		va_body[i * 6 + 4].position = sf::Vector2f({ body.at(i).first * unitSize, body.at(i).second * unitSize + unitSize });
		va_body[i * 6 + 5].position = sf::Vector2f({ body.at(i).first * unitSize + unitSize, body.at(i).second * unitSize + unitSize });

		va_body[i * 6 + 0].color = sf::Color::Green;
		va_body[i * 6 + 1].color = sf::Color::Green;
		va_body[i * 6 + 2].color = sf::Color::Green;
		va_body[i * 6 + 3].color = sf::Color::Green;
		va_body[i * 6 + 4].color = sf::Color::Green;
		va_body[i * 6 + 5].color = sf::Color::Green;
	}
}

void Snake::draw(sf::RenderTarget& target) {
	target.draw(va_body);
}


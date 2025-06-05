#ifndef SNAKE
#define SNAKE

#include <SFML/Graphics.hpp>
#include <vector>

namespace snakeGame {

enum Direction {up, left, down, right};

class Snake {
private:
	bool alive;

	int bodyLength;
	float unitSize;
	Direction movingDirection;
	std::vector<std::pair<int, int>> body;
	std::vector<std::pair<int, int>> bodyNew;
	sf::VertexArray va_body;

public:
	Snake(int initalLength, int initalPositionX, int initalPositionY, float unitsize = 50.f, Direction initialDirection = up);
	~Snake();
	void dead();
	bool isDead();
	bool isHitSelf();
	std::pair<int, int> getHead();
	std::pair<int, int> getHeadNew();
	Direction getDirection();
	void setDirection(Direction target);
	std::vector<std::pair<int, int>> getBody();
	std::vector<std::pair<int, int>> getBodyNew();
	void move(bool prolong);
	void update();
	void draw(sf::RenderTarget& target);
};


}


#endif // SNAKE
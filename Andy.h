#pragma once
#include "Header.h"
#include "Player.h"
class Andy : public Actor {
public:
	int damage;
	int health;
	sf::Vector2f direction;
	Andy(sf::Sprite sprite, int x, int y);
	Andy(const Andy &monster);
	Andy();
	void setDirection(sf::Vector2f playerPosition);
};
#include "Andy.h"

Andy::Andy(sf::Sprite sprite, int x, int y) : Actor(sprite, x, y) {
	this->damage = 2;
	this->health = 5000;
	this->direction = sf::Vector2f(0, 0);
}

Andy::Andy() {
	this->damage = 2;
	this->health = 5000;
}

void Andy::setDirection(sf::Vector2f playerPosition) {// sets the direction in which the monster should move...this function is called every frame
	float SlopeX = playerPosition.x - this->x;
	float SlopeY = playerPosition.y - this->y;
	sf::Vector2f normal(SlopeX, SlopeY);
	normal = normalizeV(normal);
	this->direction = normal;
}

Andy::Andy(const Andy & monster) {// copy constructor
	this->damage = monster.damage;
	this->direction = monster.direction;
	this->sprite = monster.sprite;
	this->x = monster.x;
	this->y = monster.y;
	this->sprite.setOrigin(225, 225);
	this->health = monster.health;
}
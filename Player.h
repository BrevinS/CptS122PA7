#pragma once
#include "Header.h"
#include "Actor.h"
class Player : public Actor{
public:
	float health;
	int score;
	int damage;
	Player(sf::Sprite sprite, float x, float y);
};
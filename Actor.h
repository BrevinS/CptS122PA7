#pragma once
#include "Header.h"
class Actor {
public:
	Actor();
	sf::Sprite sprite;
	float x;
	float y;
	Actor(sf::Sprite sprite1,float xPos,float yPos);
	//Virtual but no need for change as this is procisely used for BOTH classes Player && Enemy
	void virtual move(float x,float y);
	void virtual draw(sf::RenderWindow & window);
	void rotate(float degrees);
};
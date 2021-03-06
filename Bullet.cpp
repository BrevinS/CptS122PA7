#include "Bullet.h"

Bullet::Bullet() {
	this->direction = sf::Vector2f(0, 0);
	this->x = 500;
	this->y = 500;
}
Bullet::Bullet(const Bullet & bullet) {//copy constructor
	this->direction = bullet.direction;
	this->sprite = bullet.sprite;
	this->x = bullet.x;
	this->y = bullet.y;
}

sf::Vector2f normalizeV(const sf::Vector2f & source)// takes a vector and normalizes its length to one
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	if (length != 0)
		return sf::Vector2f(source.x / length, source.y / length);
	else
		return source;
}

Bullet::Bullet(sf::Sprite sprite3, sf::Vector2f start, sf::Vector2f mousePosition) : Actor(sprite3, start.x, start.y) {// bullet constructor
	sf::Vector2f normal;
	sf::Vector2f finalV;
	float SlopeX = mousePosition.x - start.x;
	float SlopeY = mousePosition.y - start.y;
	float angleTemp = atan2(SlopeY, SlopeX);//calculates angle for sprite to be rotated towards mouse pointer
	angleTemp = angleTemp * (180.0 / 3.141592653589793238463);// converts to degrees
	normal.y = SlopeY;
	normal.x = SlopeX;
	finalV = normalizeV(normal);
	this->angle = angleTemp - 90;
	this->sprite.setOrigin(10, 20);// makes sure that these numbers are the center of the x,y coordinates of the bullet image
	this->sprite.setRotation(angleTemp - 90);
	this->direction = finalV;
	this->framesAlive = 0;
}
void Bullet::addFrame() {// adds to the amount of frames the bullet has been alive for
	this->framesAlive += 1;
}
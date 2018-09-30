#include "Player.h"

Player::Player(sf::Sprite sprite, float x, float y) : Actor(sprite, x, y) {
	this->health = 100;
	this->sprite.setOrigin(36, 45);// set x,y coordinates to center of player image
	this->damage = 50;
}
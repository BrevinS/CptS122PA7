#pragma once

#include "Header.h"
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu(float width, float length);
	~Menu();

	void draw(sf::RenderWindow &window);
	void goUp();
	void goDown();
	int selectItem()
	{
		return mSelect;
	}

private:
	int mSelect;
	sf::Font font;
	sf::Text menu[2];
};
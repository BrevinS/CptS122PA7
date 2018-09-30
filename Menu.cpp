#include "Menu.h"

Menu::Menu(float width, float length)
{
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(width / 2, length / 4));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("EXIT");
	menu[1].setPosition(sf::Vector2f(width / 2, length / 8));

	mSelect = 0;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::goUp()
{
	if (mSelect - 1 > 0)
	{
		menu[mSelect].setColor(sf::Color::White);
		mSelect--;
		menu[mSelect].setColor(sf::Color::Red);
	}
}

void Menu::goDown()
{
	if (mSelect + 1 < 2)
	{
		menu[mSelect].setColor(sf::Color::White);
		mSelect++;
		menu[mSelect].setColor(sf::Color::Red);
	}
}
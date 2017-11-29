#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/arial.ttf"))
	{

	}

	for (size_t i = 0; i < Items_Menu; i++)
	{
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setString(tab_text_menu[i]);
		menu[i].setPosition(width / 2, height / (Items_Menu + 1) * i + 100);
	}

	selectedItemIndex = 1;
	menu[1].setFillColor(sf::Color::Red);
}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (size_t i = 0; i < Items_Menu; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < Items_Menu)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::GetPressedItem()
{
	return selectedItemIndex;
}

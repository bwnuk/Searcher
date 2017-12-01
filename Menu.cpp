#include "Menu.h"


Menu::Menu(float width, float height)
{
	try {
		if (!background_texture.loadFromFile("images/menu_background.jpg"))
		{
			throw("Background image error");
		}

		

		if (!font.loadFromFile("font/arial.ttf"))
		{
			throw("Font error");
		}
		title.setCharacterSize(50);
		title.setFont(font);
		title.setFillColor(sf::Color::Blue);
		title.setString("Searcher");
		title.setPosition(width / 2.6f, 90);

		for (size_t i = 0; i < Items_Menu; i++)
		{
			menu[i].setFont(font);
			menu[i].setCharacterSize(20);
			menu[i].setFillColor(sf::Color::White);
			menu[i].setString(tab_text_menu[i]);
			menu[i].setPosition(width / 2.1f, (height) / (Items_Menu + 4) * i + 200);
		}

		selectedItemIndex = 0;
		menu[0].setFillColor(sf::Color::Red);

	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
	background_sprite.setTexture(background_texture);
	
}

Menu::~Menu()
{
}

void Menu::Draw(sf::RenderWindow &window)
{
	window.draw(background_sprite);
	window.draw(title);
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

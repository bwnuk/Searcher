#include "SFML\Graphics.hpp"
#include <string.h>
#include <iostream>
#include "Play.h"

#define Items_Menu 3

class Menu
{
public:
	Menu(float width, float height, sf::View& view);
	~Menu();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	void LoadPart();
	void PlayPart(sf::RenderWindow& window, sf::View& view);

	int GetPressedItem();

private:
	std::string tab_text_menu[Items_Menu] = {"Play", "Load", "Exit"};
	int selectedItemIndex;

	sf::Texture background_texture;
	sf::Sprite background_sprite;
	sf::Font font;
	sf::Text menu[Items_Menu];
	sf::Text title;
};


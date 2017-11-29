#include "SFML\Graphics.hpp"
#include <string.h>

#define Items_Menu 3

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem();

private:
	std::string tab_text_menu[Items_Menu] = {"Play", "Load", "Exit"};
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[Items_Menu];
};


#include <SFML/Graphics.hpp>
#include "Menu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Searcher", sf::Style::Titlebar | sf::Style::Close);
	sf::Event evnt;

	Menu menu(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{
		
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:

				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window.close();
					break;

				//UP AND DOWN PRESSED
				case sf::Keyboard::Up:
					menu.MoveUp();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					break;
				
				//ENTER PRESSED
				case sf::Keyboard::Return:
					switch (menu.GetPressedItem())
					{
					case 0:
						break;
					case 1:
						break;
					case 2:
						window.close();
						break;
					default:
						break;
					}
					break;

				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		window.clear();
		menu.Draw(window);
		window.display();
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include "Menu.h"

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Searcher", sf::Style::Titlebar | sf::Style::Close);
	sf::Event evnt;
	sf::View view;
	//view.setCenter(0, 0);

	Menu menu(window.getSize().x, window.getSize().y, view);

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
						menu.PlayPart(window, view);
						break;
					case 1:
						menu.LoadPart();
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
		//window.setView(view);
		window.display();
	}

	return 0;
}
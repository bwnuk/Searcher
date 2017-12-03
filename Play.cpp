#include "Play.h"

Play::Play(sf::RenderWindow& w, sf::View& v)
{
	window = &w;
	view = &v;
	try
	{
		if (!font_text.loadFromFile("font/arial.ttf"))
		{
			throw("Font error");
		}
		map.loadFromFile("images/1lvl.png");
		look.setTexture(map);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

}


Play::~Play()
{
}

void Play::Settup()
{
	while (window->isOpen())
	{
		sf::Event evnt;
		while (window->pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			case sf::Event::KeyPressed:
				switch (evnt.key.code)
				{
				case sf::Keyboard::Escape:
					window->close();
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		Draw();
	}
}

void Play::Draw()
{
	window->draw(look);
	window->display();
}

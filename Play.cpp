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
		look.setOrigin(map.getSize().x/2.0f, map.getSize().y / 2.0f);
		look.setScale(sf::Vector2f(1.2f, 1.4f));
		view->setCenter(look.getPosition());
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
	float deltatime = 0.0f;
	player_texture.loadFromFile("images/player.png");

	Player player(player_texture, sf::Vector2f(9, 4), 2.0f, 0.2f, 140.0f, 0.0f, 0.0f);
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
		player.Update(deltatime);
		Draw(player);
	}
}

void Play::Draw(Player &p)
{
	window->clear();
	window->setView(*view);
	window->draw(look);
	p.Draw(*window);
	window->display();
}

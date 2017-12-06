#include "Play.h"

Play::Play(sf::RenderWindow& w, sf::View& v)
{
	window = &w;
	view = &v;

	try
	{
		//Reading font
		if (!font_text.loadFromFile("font/arial.ttf"))
			throw("Font error");

		//Reading background texture, setting background
		if (!map.loadFromFile("images/1lvl.png"))
			throw("Background error");
		
		look.setTexture(map);
		look.setScale(sf::Vector2f(1.2f, 1.4f));
		look.setOrigin(map.getSize().x/2.0f, map.getSize().y / 2.0f);


		
		sizeBG = sf::Vector2f(map.getSize());
		sizeBG.x *= 1.2f;
		sizeBG.y *= 1.4f;

		view->setCenter(look.getPosition());

		//Reading player textur, creating player
		if (!player_texture.loadFromFile("images/player.png"))
			throw("Player image error");


		player = Player(player_texture, sf::Vector2f(9, 4), 1.3f, 0.1f, 100.0f, 0.0f, 0.0f);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		w.close();
	}
}


Play::~Play()
{
	player.~Player();
}

void Play::Settup()
{
	sf::Texture t;
	t.loadFromFile("images/wut.png");
	while (window->isOpen())
	{
		float deltatime = clock.restart().asSeconds();

		upLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, -(sizeBG.y)/2.0f-20.0f));
		leftLock = Collision(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(-(sizeBG.x)/2.0f, 0.0f));
		rightLock = Collision(nullptr,sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(sizeBG.x/2.0f+5.f, sizeBG.y / 2.0f));
		downLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(sizeBG.x / 2.0f, sizeBG.y/2.0f-30.f));

		sf::Event evnt;

		//Checking if have to close
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

		//Locking room
		upLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		rightLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		leftLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		downLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

		player.Update(deltatime);
		Draw();
	}
}

void Play::Draw()
{
	//Drawing on the screen
	window->clear();
	window->setView(*view);
	window->draw(look);
	player.Draw(*window);
	try
	{
		window->display();
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}
}

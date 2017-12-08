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

		player = Player(player_texture, sf::Vector2f(9, 4), 1.3f, 0.1f, 100.0f, sf::Vector2f(0.0f, 0.0f));

		if (!enemy_pirate__texture.loadFromFile("images/piratess.png"))
			throw("Enemy image error");

		pirate = Enemy(enemy_pirate__texture, sf::Vector2f(9, 4),sf::Vector2f(100.0f,100.0f), 1.3f, 90 ,  0.1f, 2);
		
		if (!enemy_knight_texture.loadFromFile("images/bad.png"))
			throw("Enemy image error");

		knight = Enemy(enemy_knight_texture, sf::Vector2f(3, 4), sf::Vector2f(-100.0f, -120.0f), 1.3f, 60, 0.1f, 2);

		if (!enemy_magic_texture.loadFromFile("images/wut.png"))
			throw("Enemy image error");

		magic = Enemy(enemy_magic_texture, sf::Vector2f(3, 4), sf::Vector2f(200.0f, 200.0f), 1.3f, 60, 0.1f, 2);

		if (!key_texture.loadFromFile("images/key.png"))
			throw("Key image error");
		key = Object(key_texture, sf::Vector2f(30.f,30.f), sf::Vector2f(-150.f,-150.f));

		if (!chat_texture.loadFromFile("images/stone.jpg"))
			throw("Chat image error");
		if (!r.loadFromFile("images/stone.jpg"))
			throw("Chat image error");
		
		key_communicat = Communicat( chat_texture);
		key_found = false;
		
		communicat_text.setFont(font_text);
		communicat_text.setFillColor(sf::Color::Blue);
		communicat_text.setCharacterSize(50);
		communicat_text.setPosition(-200, 330);

		lose_text.setFont(font_text);
		lose_text.setFillColor(sf::Color::White);
		lose_text.setCharacterSize(100);
		lose_text.setPosition(0, 0);
		lose_text.setString("You lost!");
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
	while (window->isOpen())
	{
		float deltatime = ClockRestart();
		Locks();
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

		CollisionsCheck();
		magic.Update(deltatime);
		knight.Update(deltatime);
		pirate.Update(deltatime);
		player.Update(deltatime);
		Draw();
	}
}

void Play::Locks()
{
	upLock = Collision(&r, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, -(sizeBG.y) / 2.0f - 20.0f));
	leftLock = Collision(&r, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(-(sizeBG.x) / 2.0f, 0.0f));
	rightLock = Collision(&r, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(sizeBG.x / 2.0f + 5.f, 0.0f));
	downLock = Collision(&r, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(sizeBG.x / 2.0f, sizeBG.y / 2.0f - 30.f));
}

void Play::CollisionsCheck()
{
	//Locking room
	upLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	rightLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	leftLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	downLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

	if (key.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
	{
		key_found = true;
		communicat_text.setString("You found key");	
	}

	if (upLock.GetCollider().CheckCollision(pirate.GetCollider(), 1.0f))
	{
		pirate.setDirection(3);
	
	}
	else if (downLock.GetCollider().CheckCollision(pirate.GetCollider(), 1.0f))
	{
		pirate.setDirection(2);
	}

	if (upLock.GetCollider().CheckCollision(knight.GetCollider(), 1.0f))
	{
		knight.setDirection(3);

	}
	else if (downLock.GetCollider().CheckCollision(knight.GetCollider(), 1.0f))
	{
		knight.setDirection(2);
	}


	if (upLock.GetCollider().CheckCollision(magic.GetCollider(), 1.0f))
	{
		magic.setDirection(3);

	}
	else if (downLock.GetCollider().CheckCollision(magic.GetCollider(), 1.0f))
	{
		magic.setDirection(2);
	}

	if (player.GetCollider().CheckCollision(pirate.GetCollider(), 0.0f))
	{
		Lose();
	}
	if(player.GetCollider().CheckCollision(magic.GetCollider(), 0.0f))
	{
		Lose();
	}
	if (player.GetCollider().CheckCollision(knight.GetCollider(), 0.0f))
	{
		Lose();
	}
}

void Play::Draw()
{
	//Drawing on the screen
	window->clear();
	window->setView(*view);
	window->draw(look);
	pirate.Draw(*window);
	magic.Draw(*window);
	knight.Draw(*window);
	player.Draw(*window);
	key.Draw(*window);

	if (key_found)
	{
		key_communicat.Draw(window);
		window->draw(communicat_text);
	}
		
	window->display();
}

void Play::Lose()
{
	window->clear();
	window->setView(*view);
	window->draw(lose_text);
	window->display();
	sf::Event evnt;
	while (evnt.KeyPressed != sf::Keyboard::Return)
	{
		if (evnt.KeyPressed == sf::Keyboard::Return)
			break;
	}

	window->close();
}

float Play::ClockRestart()
{
	return clock.restart().asSeconds();
}

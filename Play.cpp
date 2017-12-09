#include "Play.h"

Play::Play(sf::RenderWindow& w, sf::View& v)
{
	window = &w;
	view = &v;

	//Reading font
	if (!font_text.loadFromFile("font/arial.ttf"))
		throw("Font error");

	//Reading background texture, setting background
	if (!map.loadFromFile("images/1lvl.png"))
		throw("Background error");

	look.setTexture(map);
	look.setScale(sf::Vector2f(1.0f, 1.0f));
	look.setOrigin(map.getSize().x / 2.0f, map.getSize().y / 2.0f);

	sizeBG = sf::Vector2f(map.getSize());

	view->setCenter(look.getPosition());

	//Reading player textur, creating player
	if (!player_texture.loadFromFile("images/player.png"))
		throw("Player image error");

	player = Player(player_texture, sf::Vector2f(9, 4), sf::Vector2f(0.0f, 0.0f), 1.3f, 0.1f, 100.0f);

	if (!enemy_pirate__texture.loadFromFile("images/piratess.png"))
		throw("Enemy image error");

	pirate = Enemy(enemy_pirate__texture, sf::Vector2f(9, 4), sf::Vector2f(100.0f, 100.0f), 1.3f, 0.1f, 90, 2);

	if (!enemy_knight_texture.loadFromFile("images/bad.png"))
		throw("Enemy image error");

	knight = Enemy(enemy_knight_texture, sf::Vector2f(3, 4), sf::Vector2f(-100.0f, -120.0f), 1.3f, 0.1f, 90, 2);

	if (!enemy_magic_texture.loadFromFile("images/wut.png"))
		throw("Enemy image error");

	magic = Enemy(enemy_magic_texture, sf::Vector2f(3, 4), sf::Vector2f(200.0f, 200.0f), 1.3f, 0.1f, 90, 2);

	if (!key_texture.loadFromFile("images/key.png"))
		throw("Key image error");
	key = Object(key_texture, sf::Vector2f(30.f, 30.f), sf::Vector2f(-150.f, -200.f));

	if (!chat_texture.loadFromFile("images/stone.jpg"))
		throw("Chat image error");
	if (!r.loadFromFile("images/stone.jpg"))
		throw("Chat image error");

	key_communicat = Communicat(chat_texture);
	key_found = false;

	communicat_text.setFont(font_text);
	communicat_text.setFillColor(sf::Color::Blue);
	communicat_text.setCharacterSize(50);
	communicat_text.setPosition(-200, 330);

	test.setFont(font_text);
	test.setFillColor(sf::Color::Blue);
	test.setCharacterSize(50);
	test.setPosition(0, 0);
	test.setString("Test");

	lose_text.setFont(font_text);
	lose_text.setFillColor(sf::Color::White);
	lose_text.setCharacterSize(100);
	lose_text.setPosition(0, 0);
	lose_text.setString("You lost!");
	Locks();
	Doors();
	test_1 = false;
}

Play::~Play()
{
	player.~Player();
}

void Play::Locks()
{
	upLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, -(sizeBG.y) / 2.0f - 20.0f));
	leftLock = Collision(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(-(sizeBG.x / 2.0f), 0.0f));
	rightLock = Collision(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(sizeBG.x / 2.0f + 5.f, 0.0f));
	downLock = Collision(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(0.0f, sizeBG.y / 2.0f - 30.f));
}

void Play::Doors()
{
	leftDoor = Collision(nullptr, sf::Vector2f(18, 20), sf::Vector2f(-(sizeBG.x / 2.0f), -50.0f));
	rightDoor = Collision(nullptr, sf::Vector2f(18, 20), sf::Vector2f(sizeBG.x / 2.0f, -50.0f));
	downDoor = Collision(&nullptr, sf::Vector2f(16, 20), sf::Vector2f(-15.0f, sizeBG.y / 2.0f-25));
}



void Play::Settup()
{
	while (window->isOpen())
	{
		float deltatime = ClockRestart();
		
		
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

void Play::CollisionsCheck()
{
	//Locking room
	upLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	rightLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	leftLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
	downLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

	if (downDoor.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
		test_1 = true;

	if (leftDoor.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
		test_1 = true;

	if (rightDoor.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
		test_1 = true;

	if (key.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
	{
		key_found = true;
		communicat_text.setString("You found key");	
	}

	BotsMove();
	PlayerBotsCollision();
}

void Play::Draw()
{
	//Drawing on the screen
	window->clear();
	window->setView(*view);
	window->draw(look);
	leftDoor.Draw(*window);
	rightDoor.Draw(*window);
	downDoor.Draw(*window);

	pirate.Draw(*window);
	magic.Draw(*window);
	knight.Draw(*window);

	key.Draw(*window);
	
	player.Draw(*window);

	if (key_found)
	{
		key_communicat.Draw(window);
		window->draw(communicat_text);
	}

	if (test_1)
		window->draw(test);
		
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

void Play::BotChangeDirection(Enemy& p, Collision& one, Collision& two)
{
	if (one.GetCollider().CheckCollision(p.GetCollider(), 1.0f))
	{
		p.setDirection(3);

	}
	else if (two.GetCollider().CheckCollision(p.GetCollider(), 1.0f))
	{
		p.setDirection(2);
	}
}

void Play::BotsMove()
{
	BotChangeDirection(pirate, upLock, downLock);
	BotChangeDirection(knight, upLock, downLock);
	BotChangeDirection(magic, upLock, downLock);
}

void Play::PlayerBotCollision(Enemy& p)
{
	if (player.GetCollider().CheckCollision(p.GetCollider(), 0.0f))
	{
		//Lose();
	}
}

void Play::PlayerBotsCollision()
{
	PlayerBotCollision(pirate);
	PlayerBotCollision(knight);
	PlayerBotCollision(magic);
}

float Play::ClockRestart()
{
	return clock.restart().asSeconds();
}

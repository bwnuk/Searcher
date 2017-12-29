#include "Play.h"

Play::Play(sf::RenderWindow& w, sf::View& v)
{
	window = &w;
	view = &v;

	Texture_reading();
	Sprites_Settup();

	sizeBG = sf::Vector2f(lvl1_t.getSize());

	view->setCenter(lvl1_s.getPosition());

	map_coutner = 0;
	
	//Reading player textur, creating player
	if (!player_texture.loadFromFile("images/player.png"))
		throw("Player image error");

	player = Player(player_texture, sf::Vector2f(9, 4), sf::Vector2f(0.0f, 0.0f), 1.3f, 0.1f, 100.0f);

	if (!chat_texture.loadFromFile("images/stone.jpg"))
		throw("Chat image error");

	communicat = Communicat(chat_texture);
	comunicat_show = false;
	if (!font_text.loadFromFile("font/arial.ttf"))
		throw("Font error");
	communicat_text.setFont(font_text);
	communicat_text.setFillColor(sf::Color::Blue);
	communicat_text.setCharacterSize(50);
	communicat_text.setPosition(-370, 310);
	Doors();
	Locks();

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

void Play::Sprites_Settup()
{
	lvl1_s.setTexture(lvl1_t);
	lvl1_s.setScale(sf::Vector2f(1.0f, 1.0f));
	lvl1_s.setOrigin(lvl1_t.getSize().x / 2.0f, lvl1_t.getSize().y / 2.0f);

	lvl2_s.setTexture(lvl2_t);
	lvl2_s.setScale(sf::Vector2f(1.0f, 1.0f));
	lvl2_s.setOrigin(lvl2_t.getSize().x / 2.0f, lvl2_t.getSize().y / 2.0f);

	lvl3_s.setTexture(lvl3_t);
	lvl3_s.setScale(sf::Vector2f(1.0f, 1.0f));
	lvl3_s.setOrigin(lvl3_t.getSize().x / 2.0f, lvl3_t.getSize().y / 2.0f);
}

void Play::Doors()
{
	leftDoor = Collision(nullptr, sf::Vector2f(18, 20), sf::Vector2f(-(sizeBG.x / 2.0f), -50.0f));
	rightDoor = Collision(nullptr, sf::Vector2f(18, 20), sf::Vector2f(sizeBG.x / 2.0f, -50.0f));
	downDoor = Collision(nullptr, sf::Vector2f(16, 20), sf::Vector2f(-15.0f, sizeBG.y / 2.0f - 25));
	upDoor = Collision(nullptr, sf::Vector2f(16, 20), sf::Vector2f(-15.0f, -sizeBG.y / 2.0f - 25));
}

void Play::Settup()
{
	Maps_Settup();
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

		Player_Doors_Map();

		maps[map_coutner].Player_Lock(player, map_coutner);
		maps[map_coutner].Player_Bots(player, window);

		if (maps[map_coutner].Player_Others(player))
		{
			switch (map_coutner)
			{
			case 0:
				communicat_text.setString("<PUZZLE> You need to find 2 buttons\nSolution: \nLEFT and Right Corner");
				comunicat_show = true;
				break;
			case 1:
				button_counter++;

				if (button_counter == 2)
				{
					communicat_text.setString("You clicked two buttons");
					comunicat_show = true;
				}
				else if (button_counter == 1)
				{
					comunicat_show = true;
					communicat_text.setString("You clicked one button");
				}

				break;
			case 2:
				communicat_text.setString("YOU FOUND KEY");
				comunicat_show = true;
				break;
			default:
				break;
			}
		}
		maps[map_coutner].Figures_Direction();
		maps[map_coutner].Bots_Update(deltatime);

		player.Update(deltatime);
		
		Draw();
	}
}


void Play::Player_Doors_Map()
{
	if (maps[map_coutner].Player_Doors(player))
	{
		if (player.GetPosition().x > 100 || player.GetPosition().x < -100)
		{
			if (player.GetPosition().x > 100)
			{
				//right
				if (map_coutner != 0)
				{
					map_coutner++;
					player.SetPosition(sf::Vector2f(-player.GetPosition().x, player.GetPosition().y));
				}
			}
			else
			{
				//left
				if (map_coutner != 0)
				{
					player.SetPosition(sf::Vector2f(-player.GetPosition().x, player.GetPosition().y));
					map_coutner--;
				}
			}
		}
		else
		{
			if (player.GetPosition().y > 120)
			{
				//Down
				map_coutner++;
				player.SetPosition(sf::Vector2f(player.GetPosition().x, -player.GetPosition().y));
			}
			else
			{
				//Up
				map_coutner--;
				player.SetPosition(sf::Vector2f(player.GetPosition().x, -player.GetPosition().y - 50.0f));
			}
		}
	}
}

void Play::Texture_reading()
{
	try 
	{
		if (!lvl1_t.loadFromFile("images/1lvl.png"))
			throw("Background error");
		if (!lvl2_t.loadFromFile("images/2lvl.png"))
			throw("Background error");
		if (!lvl3_t.loadFromFile("images/3lvl.png"))
			throw("Background error");
	}
	catch (std::exception& w)
	{
		std::cout << w.what();
		
	}
}

void Play::Maps_Settup()
{
	Enemy pirate;
	Enemy knight;

	Object sign;
	Object key;
	Object button_1;
	Object button_2;

	Doors();
	
	if (!sign_texture.loadFromFile("images/sign.png"))
		std::cout << "Key image error";
	sign = Object(&sign_texture, sf::Vector2f(50.f, 50.f), sf::Vector2f(200.f, -220.f));
	
	//
	Map lvl_1(lvl1_s, *view);
	lvl_1.set_Doors(rightDoor, downDoor, leftDoor);
	lvl_1.Locks_Settup(upLock, downLock, leftLock, rightLock);
	sign.Set_Type(0);
	lvl_1.set_Others(sign);
	maps.push_back(lvl_1);

	
	if (!enemy_pirate__texture.loadFromFile("images/piratess.png"))
		std::cout << "Enemy image error";

	pirate = Enemy(enemy_pirate__texture, sf::Vector2f(9, 4), sf::Vector2f(100.0f, 100.0f), 1.3f, 0.1f, 100, 2);
	pirate.setOneTwo(3, 2);

	button_1 = Object(nullptr, sf::Vector2f(25.f, 25.f), sf::Vector2f(-200.f, 220.f));
	button_2 = Object(nullptr, sf::Vector2f(25.f, 25.f), sf::Vector2f(-200.f, -220.f));
	button_counter = 0;
	button_1.Set_Type(1);
	button_2.Set_Type(1);

	Map lvl_2(lvl2_s, *view, pirate);
	lvl_2.set_Doors(upDoor, rightDoor);
	lvl_2.Locks_Settup(upLock, downLock, leftLock, rightLock);
	lvl_2.set_Others(button_1, button_2);
	maps.push_back(lvl_2);


	if (!enemy_knight_texture.loadFromFile("images/bad.png"))
		std::cout << "Enemy image error";
	knight = Enemy(enemy_knight_texture, sf::Vector2f(3, 4), sf::Vector2f(-20.0f, -150.0f), 1.3f, 0.1f, 100, 2);
	knight.setOneTwo(3, 2);

	if (!key_texture.loadFromFile("images/key.png"))
		std::cout << "Key image error";
	key = Object(&key_texture, sf::Vector2f(30.f, 30.f), sf::Vector2f(220.f, -210.f));

	Map lvl_3(lvl3_s, *view, pirate, knight);
	lvl_3.set_Doors(leftDoor);
	key.Set_Type(2);
	lvl_3.set_Others(key);
	lvl_3.Locks_Settup(upLock, downLock, leftLock, rightLock);
	maps.push_back(lvl_3);
}

float Play::ClockRestart()
{
	return clock.restart().asSeconds();
}

void Play::Draw()
{
	maps[map_coutner].Draw(window);
	player.Draw(*window);
	communicat.Draw(window);
	if (comunicat_show)
	{
		
		window->draw(communicat_text);
	}
	window->display();
}
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
	Doors();
	test_1 = false;
}

Play::~Play()
{
	player.~Player();
}

void Play::Sprites_Settup()
{
	lvl1_s.setTexture(lvl2_t);
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
	upDoor = Collision(nullptr, sf::Vector2f(16, 20), sf::Vector2f(-15.0f, -(sizeBG.y / 2.0f - 25)));
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

		maps[map_coutner].Figures_Direction();
		maps[map_coutner].Player_Doors(player);
		maps[map_coutner].Player_Lock(player);
		maps[map_coutner].Player_Bots(player, window);
		maps[map_coutner].Player_Others(player);
		
		player.Update(deltatime);
		
		Draw();
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
	sf::Texture enemy_knight_texture;
	sf::Texture enemy_pirate__texture;
	Enemy pirate;
	Enemy knight;
	Object key;

	Doors();
	
	//
	Map lvl_1(lvl1_s, *view);
	lvl_1.set_Doors(rightDoor, downDoor, upDoor);
	maps.push_back(lvl_1);

	//
	if (!enemy_pirate__texture.loadFromFile("images/piratess.png"))
		std::cout << "Enemy image error";

	pirate = Enemy(enemy_pirate__texture, sf::Vector2f(9, 4), sf::Vector2f(100.0f, 100.0f), 1.3f, 0.1f, 90, 2);

	Map lvl_2(lvl2_s, *view, pirate);
	lvl_2.set_Doors(upDoor, rightDoor);
	maps.push_back(lvl_2);


	if (!enemy_knight_texture.loadFromFile("images/bad.png"))
		std::cout << "Enemy image error";

	knight = Enemy(enemy_knight_texture, sf::Vector2f(3, 4), sf::Vector2f(-100.0f, -120.0f), 1.3f, 0.1f, 90, 2);
	
	if (!key_texture.loadFromFile("images/key.png"))
		throw("Key image error");
	key = Object(key_texture, sf::Vector2f(30.f, 30.f), sf::Vector2f(-150.f, -200.f));

	Map lvl_3(lvl2_s, *view, pirate, knight);
	lvl_3.set_Doors(leftDoor);
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
	window->display();
}
#include <SFML\Graphics.hpp>
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include "Player.h"
#include "Collision.h"
#include "Object.h"
#include "Communicat.h"
#include "Enemy.h"
#include "Map.h"
#include <vector>

class Play: public Collision
{
public:
	Play(sf::RenderWindow& w, sf::View& v);
	~Play();

	void Locks();
	void Sprites_Settup();
	void Doors();
	void Settup();
	void CollisionsCheck();

	void Lose();
	void BotChangeDirection(Enemy& p, Collision& one, Collision& two);
	void BotsMove();
	void PlayerBotCollision(Enemy& p);
	void PlayerBotsCollision();

	void Texture_reading();
	void Maps_Settup();

	float ClockRestart();

	void Draw();
private:
	std::vector<Map> maps;

	Player player;

	
	Communicat communicat;
	bool key_found;
	bool test_1;

	Collision upLock;
	Collision downLock;
	Collision rightLock;
	Collision leftLock;

	Collision leftDoor;
	Collision downDoor;
	Collision rightDoor;
	Collision upDoor;

	sf::Vector2f sizeBG;

	sf::RenderWindow *window;
	sf::View *view;

	sf::Font font_text;
	
	sf::Sprite lvl1_s;
	sf::Sprite lvl2_s;
	sf::Sprite lvl3_s;

	sf::Texture player_texture;

	sf::Texture enemy_magic_texture;

	sf::Texture key_texture;
	sf::Texture chat_texture;

	sf::Texture lvl1_t;
	sf::Texture lvl2_t;
	sf::Texture lvl3_t;

	sf::Texture r;
	sf::Texture chat;
	sf::Texture test_t;

	sf::Text communicat_text;
	sf::Text lose_text;
	sf::Text test;

	sf::Clock clock;

	int map_coutner;
};
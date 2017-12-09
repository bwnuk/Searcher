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

class Play: public Collision
{
public:
	Play(sf::RenderWindow& w, sf::View& v);
	~Play();

	void Locks();
	void Doors();
	void Settup();
	void CollisionsCheck();
	void Draw();
	void Lose();
	void BotChangeDirection(Enemy& p, Collision& one, Collision& two);
	void BotsMove();
	void PlayerBotCollision(Enemy& p);
	void PlayerBotsCollision();

	float ClockRestart();
private:
	Player player;
	Enemy pirate;
	Enemy knight;
	Enemy magic;

	Object key;
	Communicat key_communicat;
	bool key_found;
	bool test_1;

	Collision upLock;
	Collision downLock;
	Collision rightLock;
	Collision leftLock;

	Collision leftDoor;
	Collision downDoor;
	Collision rightDoor;

	sf::Vector2f sizeBG;

	sf::RenderWindow *window;
	sf::View *view;

	sf::Font font_text;
	
	sf::Sprite look;

	sf::Texture player_texture;
	sf::Texture enemy_pirate__texture;
	sf::Texture enemy_magic_texture;
	sf::Texture enemy_knight_texture;
	sf::Texture key_texture;
	sf::Texture chat_texture;
	sf::Texture map;
	sf::Texture r;
	sf::Texture chat;
	sf::Texture test_t;

	sf::Text communicat_text;
	sf::Text lose_text;
	sf::Text test;

	sf::Clock clock;
};
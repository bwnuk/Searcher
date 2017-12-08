#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Collision.h"
#include "Object.h"
#include "Communicat.h"

class Play: public Collision
{
public:
	Play(sf::RenderWindow& w, sf::View& v);
	~Play();

	void Settup();
	void Locks();
	void CollisionsCheck();
	void Draw();
private:
	Player player;
	Object key;
	Communicat key_communicat;
	bool key_found;

	Collision upLock;
	Collision downLock;
	Collision rightLock;
	Collision leftLock;

	sf::Vector2f sizeBG;

	sf::RenderWindow *window;
	sf::View *view;

	sf::Font font_text;
	
	sf::Sprite look;

	sf::Texture player_texture;
	sf::Texture key_texture;
	sf::Texture chat_texture;
	sf::Texture map;
	sf::Texture chat;
	sf::Text communicat_text;

	sf::Clock clock;
};
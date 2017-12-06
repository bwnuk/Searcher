#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Collision.h"

class Play: public Collision
{
public:
	Play(sf::RenderWindow& w, sf::View& v);
	~Play();

	void Settup();
	void Draw();
private:
	Player player;

	Collision upLock;
	Collision downLock;
	Collision rightLock;
	Collision leftLock;

	sf::Vector2f sizeBG;

	sf::RenderWindow *window;
	sf::View *view;
	sf::Sprite look;
	sf::Font font_text;
	sf::Texture player_texture;
	sf::Texture map;
	sf::Texture chat;
	sf::Clock clock;
};


#include <SFML\Graphics.hpp>
#include <iostream>
#include "Player.h"

class Play
{
public:
	Play(sf::RenderWindow& w, sf::View& v);
	~Play();

	void Settup();
	void Draw();
private:
	Player player;

	sf::RenderWindow *window;
	sf::View *view;
	sf::Sprite look;
	sf::Font font_text;
	sf::Texture player_texture;
	sf::Texture map;
	sf::Texture chat;
	sf::Clock clock;
};


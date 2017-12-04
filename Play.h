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
	sf::RenderWindow *window;
	sf::View *view;
	sf::Sprite look;
	sf::Font font_text;

	sf::Texture map;
	sf::Texture chat;
};


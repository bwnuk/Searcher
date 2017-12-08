#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

class Communicat
{
public:
	Communicat();
	Communicat( sf::Texture& t_c);
	~Communicat();
	void Draw(sf::RenderWindow* w);

private:
	sf::Texture chat_texture;
	sf::Sprite chat_sprite;
};
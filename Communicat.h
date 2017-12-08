#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <fstream>

class Communicat
{
public:
	Communicat();
	Communicat(sf::RenderWindow& ww,  sf::Texture& b);
	~Communicat();
	
	void setPosition(sf::Vector2f f);
private:
	sf::RenderWindow* w;
	sf::Text text_to_show;
	std::string string_text;
	sf::Font f;
	sf::Sprite background_all;
	sf::Texture* background_com;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};


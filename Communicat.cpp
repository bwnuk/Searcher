#include "Communicat.h"

Communicat::Communicat()
{
}

Communicat::Communicat(sf::RenderWindow & ww,  sf::Texture & b)
{
	w = &ww;
	background_com = &b;
	background_all.setTexture(*background_com);
	
	if (!f.loadFromFile("font/arial.ttf"))
		throw("Font error");
	
	std::fstream file;
	file.open("com/key.txt", std::ios::in);
	
	if (!file.good())
	{
		exit(1);
	}
	//std::getline(file, string_text);

	background_all.setPosition(0, 0);
	text_to_show.setString("RAZS");
	text_to_show.setFont(f);
	text_to_show.setCharacterSize(30);
	text_to_show.setPosition(20, 30);
	text_to_show.setFillColor(sf::Color::White);
}


Communicat::~Communicat()
{
}

void Communicat::setPosition(sf::Vector2f f)
{
	f.x -= w->getSize().x / 2;
	f.y += w->getSize().y / 2 - background_com->getSize().y - 5;
	background_all.setPosition(f.x, f.y);
	text_to_show.setPosition(20 + f.x, f.y + 20 + 1 * 45);
}
//
void Communicat::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(background_all);
	target.draw(text_to_show);
}

#include "Character.h"

Character::Character(sf::Texture * t, sf::Vector2f s, sf::Vector2f p)
{
	body.setSize(s);
	body.setOrigin(s / 2.0f);
	body.setTexture(t);
	body.setPosition(p);
}

Character::Character(sf::Texture * t)
{
	body.setTexture(t);
}

Character::~Character()
{
}

void Character::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

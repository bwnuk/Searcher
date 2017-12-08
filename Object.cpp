#include "Object.h"

Object::Object(sf::Texture& t, sf::Vector2f s, sf::Vector2f p)
{
	body.setSize(s);
	body.setTexture(&t);
	body.setOrigin(s / 2.0f);
	body.setPosition(p);
}

Object::~Object()
{
}

void Object::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

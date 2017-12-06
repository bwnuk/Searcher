#include "Object.h"

Object::Object(sf::Texture& texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setTexture(&texture);
	body.setPosition(position);
}

Object::~Object()
{
}

void Object::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

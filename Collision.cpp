#include "Collision.h"

Collision::Collision(sf::Texture* t, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setPosition(position);
	body.setTexture(t);
}

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Draw(sf::RenderWindow& w)
{
	w.draw(body);
}
#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

class Collision
{
public:
	Collision(sf::Texture* t, sf::Vector2f size, sf::Vector2f position);
	Collision();
	~Collision();
	void Draw(sf::RenderWindow& w);
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
};


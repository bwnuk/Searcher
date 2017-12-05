#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

class Character
{
public:
	Character(sf::Texture& t, sf::Vector2f s, sf::Vector2f p);
	Character(sf::Texture& t, float x, float y);
	~Character();


	void Draw(sf::RenderWindow& window);

	float collisionSize;
	Collider GetCollider() { return Collider(body); }

	sf::RectangleShape body;
	sf::Vector2f sizeBody;
};


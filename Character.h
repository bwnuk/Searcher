#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

class Character
{
public:

	Character(sf::Texture& texture, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float switchTime, float speed);
	//Character(sf::Texture& t, sf::Vector2f s, sf::Vector2f p);
	//Character(sf::Texture& t, sf::Vector2f p);
	Character();
	~Character();


	void Draw(sf::RenderWindow& window);

	float collisionSize;
	Collider GetCollider() { return Collider(body); }

	sf::RectangleShape body;
	sf::Vector2f sizeBody;
	float speed;
	int row;
};


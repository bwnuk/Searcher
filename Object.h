#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"


class Object
{
public:
	Object(sf::Texture* t, sf::Vector2f s, sf::Vector2f position);
	Object() {};
	~Object();

	int Get_Type();
	void Set_Type(int t);

	void Draw(sf::RenderWindow& window);
	
	Collider GetCollider() { return Collider(body); }
private:
	sf::RectangleShape body;
	float collisionSize;
	int type;
};

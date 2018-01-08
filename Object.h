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

	bool Get_Drawable();
	void Set_Drawable(bool d);

	void Draw(sf::RenderWindow& window);
	
	Collider GetCollider() { return Collider(body); }
private:
	bool drawable;
	sf::RectangleShape body;
	float collisionSize;
	int type;
};

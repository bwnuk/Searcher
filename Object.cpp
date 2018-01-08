#include "Object.h"

Object::Object(sf::Texture* t, sf::Vector2f s, sf::Vector2f p)
{
	body.setSize(s);
	body.setTexture(t);
	body.setOrigin(s / 2.0f);
	body.setPosition(p);
	drawable = true;
}

Object::~Object()
{
}

int Object::Get_Type()
{
	return type;
}

void Object::Set_Type(int t)
{
	type = t;
}

bool Object::Get_Drawable()
{
	return drawable;
}

void Object::Set_Drawable(bool d)
{
	drawable = d;
}

void Object::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}


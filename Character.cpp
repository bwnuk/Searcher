#include "Character.h"

Character::Character(sf::Texture & texture, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float switchTime, float speed)
{
	body.setTexture(&texture);
	body.setPosition(p);
	this->speed = speed;
	row = 0;

	sizeBody = sf::Vector2f(texture.getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;

	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&texture);
}

Character::Character()
{
}

Character::~Character()
{
}

void Character::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}

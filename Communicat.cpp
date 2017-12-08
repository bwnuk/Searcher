#include "Communicat.h"

Communicat::Communicat()
{
}

Communicat::Communicat(sf::Texture& t_c)
{	
	chat_sprite.setTexture(t_c);
	chat_sprite.setPosition(sf::Vector2f(-500, 300));
	chat_sprite.setScale(1.3f, 0.7f);
}

Communicat::~Communicat()
{
}

void Communicat::Draw(sf::RenderWindow* w)
{
	w->draw(chat_sprite);
}


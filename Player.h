#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Animation.h"

class Player: public Character, public Animation
{
public:
	Player();
	Player(sf::Texture& texture, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float switchTime, float speed);
	~Player();

	void Update(float deltaTime);

	sf::Vector2f GetPosition() const { return  body.getPosition(); }
private:
	bool Stay;
};


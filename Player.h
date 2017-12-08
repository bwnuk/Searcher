#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Animation.h"

class Player: public Character, public Animation
{
public:
	Player();
	Player(sf::Texture& texture, sf::Vector2f imageCount, float scale_body, float switchTime, float speed, sf::Vector2f p);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow &w);

	sf::Vector2f GetPosition() const { return  body.getPosition(); }
private:
	unsigned int row;
	float speed;
	bool Stay;
};


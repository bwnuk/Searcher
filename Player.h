#pragma once
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Animation.h"

class Player: public Character
{
public:
	Player(sf::Texture* texture, sf::Vector2f imageCount, float scale_body, float switchTime, float speed);
	~Player();
	void Update(float deltaTime);
	sf::Vector2f GetPosition() const { return  body.getPosition(); }
	enum Direction { left, right, up, down };
private:
	Direction direction;
	Animation animation;
	unsigned int row;
	float speed;
	bool Stay;
};

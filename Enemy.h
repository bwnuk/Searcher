#include "SFML\Graphics.hpp"
#include "Collider.h"
#include "Character.h"


#include "Animation.h"

#pragma once
class Enemy: public Character, public Animation
{
public:
	Enemy() {};
	Enemy(sf::Texture& t, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float switchtime, float speed, int d);
	~Enemy();

	void setDirection(int d);
	int getDirection();
	void Update(float deltaTime);
private:
	Direction direction;
	bool Stay;
};


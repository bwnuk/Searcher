#include "SFML\Graphics.hpp"
#include "Collider.h"
#include "Character.h"
#include "Animation.h"

#pragma once
class Enemy: public Character, public Animation
{
public:
	Enemy() {};
	Enemy(sf::Texture& t, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float speed, float switchtime, int d);
	~Enemy();

	void setDirection(int d);
	int getDirection();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& w);
private:
	Direction direction;
	unsigned int row;
	float speed;
	bool Stay;
};


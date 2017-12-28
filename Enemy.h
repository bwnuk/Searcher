#include "SFML\Graphics.hpp"
#include "Collider.h"
#include "Character.h"
#include "Collision.h"
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

	int getOne();
	int getTwo();
	void setOneTwo(int o, int t);

	void Update(float deltaTime);
	Collision one;
	Collision two;
private:
	Direction direction;
	bool Stay;
	int one, two;
};


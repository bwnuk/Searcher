#include "Enemy.h"


Enemy::Enemy(sf::Texture & t, sf::Vector2f imageCount,  sf::Vector2f p,  float scale_body,  float switchtime, float speed, int d)
	:Character(t, imageCount, p, scale_body, switchtime, speed), Animation(t, imageCount, switchtime)
{
	direction = (Direction) d;
	Stay = false;
}

Enemy::~Enemy()
{
}

void Enemy::setDirection(int d)
{
	direction = (Direction)d;
}

int Enemy::getDirection()
{
	return int(direction);
}

void Enemy::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	switch (direction)
	{
	case 0:
		movement.x -= speed*deltaTime;
		row = 3;
		break;
	case 1:
		movement.x += speed*deltaTime;
		row = 1;
		break;
	case 2:
		movement.y -= speed*deltaTime;
		row = 0;
		break;
	case 3:
		movement.y += speed*deltaTime;
		row = 2;
		break;
	default:
		exit(1);
		break;
	}
	Animation::Update(row, deltaTime, Stay);

	body.setTextureRect(uvRect);
	body.move(movement);
}

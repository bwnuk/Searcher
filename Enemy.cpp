#include "Enemy.h"


Enemy::Enemy(sf::Texture & t, sf::Vector2f imageCount,  sf::Vector2f p,  float scale_body, float speed, float switchtime, int d)
	:Character(t, p), Animation(t, imageCount, switchtime)
{
	this->speed = speed;
	row = 0;
	direction = (Direction) d;

	sizeBody = sf::Vector2f(t.getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;

	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&t);
	collisionSize = sizeBody.y + 10.0f;
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

void Enemy::Draw(sf::RenderWindow& w)
{
	w.draw(body);
}

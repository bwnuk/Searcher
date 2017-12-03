#include "Player.h"


Player::Player(sf::Texture* texture, sf::Vector2f imageCount, float scale_body, float switchTime, float speed)
	:Character(texture), animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	Stay = true;
	sizeBody = sf::Vector2f(texture->getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;
	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(500.0f, 500.0f);
	body.setTexture(texture);
	collisionSize = sizeBody.y + 10.0f;

}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += speed*deltaTime;
	if (movement.x > 0.0f)
	{
		row = 2;
		direction = right;
	}
	if (movement.x < 0.0f)
	{
		row = 1;
		direction = left;
	}

	if (movement.y < 0.0f)
	{
		row = 3;
		direction = up;
	}
	if (movement.y > 0.0f)
	{
		row = 0;
		direction = down;
	}

	Stay = false;
	if (movement.y == 0 && movement.x == 0)
		Stay = true;

	animation.Update(row, deltaTime, Stay);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

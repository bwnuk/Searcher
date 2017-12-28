#include "Player.h"


Player::Player()
{}

Player::Player(sf::Texture& texture, sf::Vector2f imageCount, sf::Vector2f p, float scale_body, float switchTime, float speed)
	:Character(texture, imageCount, p, scale_body, switchTime, speed), Animation(texture, imageCount, switchTime)
{
	Stay = true;
	collisionSize = sizeBody.y + 10.0f;
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	sf::Vector2f movement(0.0f, 0.0f);

	//Checking pressed key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		movement.y -= speed*deltaTime;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		movement.y += speed*deltaTime;

	//Checking direction
	if (movement.x > 0.0f)
	{
		row = 3;
	}
	if (movement.x < 0.0f)
	{
		row = 1;
	}

	if (movement.y < 0.0f)
	{
		row = 0;
	}
	if (movement.y > 0.0f)
	{
		row = 2;
	}

	Stay = false;

	//Stay or going
	if (movement.y == 0 && movement.x == 0)
		Stay = true;

	Animation::Update(row, deltaTime, Stay);

	body.setTextureRect(uvRect);
	body.move(movement);
}

void Player::SetPosition(sf::Vector2f p)
{
	body.setPosition(p);
}

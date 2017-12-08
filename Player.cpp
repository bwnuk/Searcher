#include "Player.h"


Player::Player()
{}

Player::Player(sf::Texture& texture, sf::Vector2f imageCount, float scale_body, float switchTime, float speed, sf::Vector2f p)
	:Character(texture, p), Animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	Stay = true;

	sizeBody = sf::Vector2f(texture.getSize());
	sizeBody.y = sizeBody.y / imageCount.y * scale_body;
	sizeBody.x = sizeBody.x / imageCount.x * scale_body;
	
	body.setSize(sizeBody);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(&texture);
	
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

void Player::Draw(sf::RenderWindow& w)
{
	w.draw(body);
}

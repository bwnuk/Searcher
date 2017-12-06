#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(sf::Texture& texture, sf::Vector2f imageCount, float switchtime)
{
	this->imageCount = imageCount;
	this->switchtime = switchtime;

	totaltime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture.getSize().x / (float)imageCount.x;
	uvRect.height = texture.getSize().y / (float)imageCount.y;
}

Animation::~Animation()
{
}

void Animation::Update(unsigned int row, float deltaTime, bool Stay)
{
	currentImage.y = row;
	totaltime += deltaTime;

	//Have to change image or not
	if (totaltime >= switchtime )
	{
		totaltime -= switchtime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y*uvRect.height;

	if (Stay)
		uvRect.left = 0 * uvRect.width;
	else
		uvRect.left = currentImage.x*uvRect.width;
}

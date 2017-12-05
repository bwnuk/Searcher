#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture& texture, sf::Vector2f imageCount, float switchtime);
	~Animation();
	void Update(unsigned int row, float deltaTime, bool Stay);
	sf::IntRect uvRect;
private:
	sf::Vector2f imageCount;
	sf::Vector2f currentImage;
	float totaltime;
	float switchtime;
};


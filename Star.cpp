#include "Star.h"



Star::Star(sf::Texture * texture, sf::Vector2f playerPos)
{
	this->shape.setTexture(*texture);
	this->shape.setScale(sf::Vector2f(0.25f, 0.25f));
	float posx, posy;
	posx = rand() % 2900 + 50;
	posy = rand() % 2900 + 50;
	while (true)
	{
		if ((posx < playerPos.x - 600) || (posx > playerPos.x + 600))
			break;
		else
			posx = rand() % 2900 + 50;
	}

	while (true)
	{
		if ((posy < playerPos.y - 600) || (posy > playerPos.y + 600))
			break;
		else
			posy = rand() % 2900 + 50;
	}

	this->shape.setPosition(sf::Vector2f(posx, posy));
}


Star::~Star()
{
}

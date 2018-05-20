#include "Enemy1.h"





Enemy1::Enemy1(sf::Texture * texture, sf::Vector2f playerPos)
{
	
	//load texture first
	this->shootTimer = 50;
	this->shape.setTexture(*texture);
	this->shape.setOrigin(sf::Vector2f(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2));
	this->shape.setScale(sf::Vector2f(0.35f, 0.35f));
	float posx, posy;
	posx = rand() % 3000;
	posy = rand() % 3000;
	while (true)
	{
		if ((posx < playerPos.x - 600) || (posx > playerPos.x + 600))
			break;
		else
			posx = rand() % 3000;
	}

	while (true)
	{
		if ((posy < playerPos.y - 600) || (posy > playerPos.y + 600))
			break;
		else
			posy = rand() % 3000;
	}

	this->shape.setPosition(sf::Vector2f(posx,posy));
	this->vx = (float)(float)(rand() % 3) + 1.0;
	this->vy = (float)(float)(rand() % 3) + 1.0;
	this->dx = rand() % 2;
	this->dy = rand() % 2;
	while (true)
	{
		this->vx = (float)(float)(rand() % 3) + 1.0;
		this->vy = (float)(float)(rand() % 3) + 1.0;
		if (this->vx != 0 && this->vy != 0) break;
	}
	this->damage = 1;
	this->HPMax = rand() % 5 + 1;
	this->HP = this->HPMax;

}

Enemy1::~Enemy1()
{
}

bool Enemy1::ifShoot(sf::Vector2f playerPos)
{
	float length = sqrt(pow((playerPos.x - shape.getPosition().x), 2) + pow((playerPos.y - shape.getPosition().y), 2));
	if (length < 350)
		return true;
	return false;
}

sf::Vector2f Enemy1::MoveEnemy(sf::Vector2f playerPos, sf::Vector2f mapSize) 
{

	if (this->shape.getPosition().x <= 0)
		this->dx = 1;
	else if (this->shape.getPosition().x + this->shape.getGlobalBounds().width >= mapSize.x)
		this->dx = 0;

	if (this->shape.getPosition().y <= 0)
		this->dy = 1;
	else if (this->shape.getPosition().y + this->shape.getGlobalBounds().height >= mapSize.y)
		this->dy = 0;

	if (this->dx)
		this->vx = abs(this->vx);
	else
		this->vx = -abs(this->vx);

	if (this->dy)
		this->vy = abs(this->vy);
	else
		this->vy = -abs(this->vy);

	return (sf::Vector2f(this->vx, this->vy));

}

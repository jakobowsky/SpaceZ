#include "Enemy2.h"

//Need to make it now

Enemy2::Enemy2(sf::Texture * texture, sf::Vector2f playerPos)
{
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

	this->shape.setPosition(sf::Vector2f(posx, posy));
	this->vx = (float)(rand() % 5) + 1.0;
	this->vy = (float)(rand() % 5) + 1.0;
	this->dx = rand() % 2;
	this->dy = rand() % 2;
	while (true)
	{
		this->vx = (float)(float)(rand() % 5) + 1.0;
		this->vy = (float)(float)(rand() % 5) + 1.0;
		if (this->vx != 0 && this->vy != 0) break;
	}
	this->damage = 3;
	this->HPMax = rand() % 5 + 1;
	this->HP = this->HPMax;
	this->attack = false;
	
	

}


Enemy2::~Enemy2()
{

}

bool Enemy2::ifShoot(sf::Vector2f playerPos)
{
	
	float length = sqrt(pow((playerPos.x - shape.getPosition().x), 2) + pow((playerPos.y - shape.getPosition().y), 2));
	if (length < 300)
	{
		this->attack = true;
		return true;
	}
		
	return false;
}

sf::Vector2f Enemy2::MoveEnemy(sf::Vector2f playerPos, sf::Vector2f mapSize)
{
	if (ifShoot(playerPos) || this->attack == true)
	{

		sf::Vector2f aimDir = playerPos - this->shape.getPosition();
		sf::Vector2f aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
		//poprawic to, musi sie poruszac w strone playera, a nie teleportowac
		return (aimDirNorm.x * 3.5f,aimDirNorm * 3.5f);
	}
	else if (this->attack == false)
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
	
}



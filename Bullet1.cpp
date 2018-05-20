#include "Bullet1.h"



Bullet1::Bullet1(sf::Texture * texture,sf::Vector2f pos, sf::Vector2f dir, float mSpeed)
	:currVelocity(0.f,0.f)
{
	this->shape.setTexture(*texture);
	this->shape.setOrigin(sf::Vector2f(this->shape.getGlobalBounds().width / 2, this->shape.getGlobalBounds().height / 2));
	this->shape.setScale(sf::Vector2f(0.15f, 0.15f));
	this->shape.setPosition(pos);
	this->maxSpeed = mSpeed;
	this->currVelocity = dir * this->maxSpeed;
}


Bullet1::~Bullet1()
{
}

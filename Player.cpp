#include "Player.h"



Player::Player(sf::Texture *texture)
{
	this->weaponPoints = 0;
	this->shield = 5;
	this->HPMax = 50;
	this->HP = this->HPMax;
	this->shape.setTexture(*texture);
	this->shape.setScale(sf::Vector2f(0.3f, 0.3f));
	this->maxVelocity = 5.f;
	this->acceleration = 1.f;
	this->drag = 0.5f;
	this->shootTimer = 20;
}




Player::~Player()
{

}

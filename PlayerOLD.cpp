#include "Player.h"
#include "AnimationClass.h"


Player::Player()
{
	this->life = 10;
}

void Player::Settings(AnimationClass &a, int X, int Y, float Angle, int radius)
{
	this->anim = a;
	this->x = X;
	this->y = Y;
	this->angle = Angle;
	this->R = radius;

}

void Player::Update(int xEnd, int yEnd)
{
	if (this->thrust)
	{
		if (this->thrust)
		{
			this->dx += cos(this->angle*DEGTORAD)*0.2;
			this->dy += sin(this->angle*DEGTORAD)*0.2;
		}
		else
		{
			this->dx *= 0.99;
			this->dy *= 0.99;
		}

		int maxSpeed = 15;
		float speed = sqrt(this->dx*this->dx + this->dy*this->dy);
		if (speed>maxSpeed)
		{
			this->dx *= maxSpeed / speed;
			this->dy *= maxSpeed / speed;
		}

		this->x += dx;
		this->y += dy;

		if (this->x>=xEnd- this->anim.sprite.getGlobalBounds().width)
			xEnd - this->anim.sprite.getGlobalBounds().width;
		if (this->x<=0)
			this->x = 0;
		if (this->y >= yEnd - this->anim.sprite.getGlobalBounds().height)
			this->y = yEnd - this->anim.sprite.getGlobalBounds().height;
		if (this->y <= 0)
			this->y = 0;


	}
}

void Player::draw(sf::RenderWindow & window)
{
	this->anim.sprite.setPosition(this->x, this->y);
	this->anim.sprite.setRotation(this->angle + 90);
	window.draw(anim.sprite);
}


Player::~Player()
{
}

#include "AnimationClass.h"


AnimationClass::AnimationClass(sf::Texture &photoOfAnimation, int x, int y, int w, int h, int count, float Speed)
{
	this->Frame = 0;
	this->speed = Speed;

	for (int i = 0; i<count; i++)
		this->frames.push_back(sf::IntRect(x + i*w, y, w, h));

	this->sprite.setTexture(photoOfAnimation);
	this->sprite.setOrigin(w / 2, h / 2);
	this->sprite.setTextureRect(frames[0]);
}


AnimationClass::~AnimationClass()
{
}

void AnimationClass::update()
{
	Frame += speed;
	int n = frames.size();
	if (Frame >= n) Frame -= n;
	if (n>0) sprite.setTextureRect(frames[int(Frame)]);
}

bool AnimationClass::isEnd()
{
	return Frame + speed >= frames.size();
}

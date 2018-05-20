#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML\Window.hpp"
#include <math.h>
#include <cstdlib>
#include <vector>
#include <string>

class AnimationClass
{
public:
	float Frame; //How many frames is in the photo
	float speed; //How fast will the frames change
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames; //vector where frames are saved
	AnimationClass();
	AnimationClass(sf::Texture &photoOfAnimation, int x,int y,int w,int h, int count, float Speed);
	void update();
	bool isEnd();
	~AnimationClass();
};


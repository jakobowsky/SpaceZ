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
#include "AnimationClass.h"

class Player
{
public:
	float DEGTORAD = 0.017453f;
	bool thrust;
	float x, y, dx, dy, R, angle;
	int life;
	int maxLife;
	AnimationClass anim;
	Player();
	void Settings(AnimationClass &a, int X, int Y, float Angle, int radius);
	void Update(int xEnd, int yEnd);
	void draw(sf::RenderWindow &window);
	~Player();
};


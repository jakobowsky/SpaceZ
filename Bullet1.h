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
class Bullet1
{
public:

	sf::Sprite shape;
	sf::Vector2f currVelocity;
	float maxSpeed;


	Bullet1(sf::Texture * texture, sf::Vector2f pos, sf::Vector2f dir,float mSpeed);

	~Bullet1();
};


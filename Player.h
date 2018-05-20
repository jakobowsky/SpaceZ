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
#include "Bullet1.h"

class Player
{
public:
	int HP;
	int HPMax;
	int score;
	int shield;
	int weaponPoints;
	sf::Vector2f currentVelocity;
	sf::Vector2f direction;
	float maxVelocity ;
	float acceleration;
	float drag; //opor
	
	int shootTimer;
	sf::Sprite shape;
	std::vector <Bullet1> bullets;
	Player(sf::Texture * texture);
	~Player();
};


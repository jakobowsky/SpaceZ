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
class Enemy2
{
public:
	int HP;
	int HPMax;
	int dx, dy; //initial direction to move
	int vx, vy; //initial velocity
	sf::Sprite shape;
	Enemy2(sf::Texture * texture, sf::Vector2f playerPos);
	~Enemy2();
	bool attack;
	bool ifShoot(sf::Vector2f playerPos);
	int damage;
	int shootTimer;
	sf::Vector2f MoveEnemy(sf::Vector2f playerPos, sf::Vector2f mapSize);
};

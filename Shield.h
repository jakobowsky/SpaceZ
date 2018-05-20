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
class Shield
{
public:
	sf::Sprite shape;
	Shield(sf::Texture * texture, sf::Vector2f playerPos);
	~Shield();
};


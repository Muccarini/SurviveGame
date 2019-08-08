#pragma once
#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation();
	~Animation();

	void animate(sf::Sprite& sprite, sf::Time deltaTime, float switchTime);
};


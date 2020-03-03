#pragma once
#include "SFML/Graphics.hpp"
#include <list> 
class StrategyMove
{
public:

	virtual ~StrategyMove() {};

	virtual void move(sf::Time deltatime, sf::Sprite& _sprite, sf::Vector2f target, 
		std::list<sf::Vector2f> &movevect, const float mov_speed) = 0;
};
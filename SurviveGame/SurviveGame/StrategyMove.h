#pragma once
#include "SFML/Graphics.hpp"

class StrategyMove
{
public:

	virtual ~StrategyMove();

	virtual void move(sf::Time deltatime, sf::Sprite& _sprite, const float mov_speed)=0;
};
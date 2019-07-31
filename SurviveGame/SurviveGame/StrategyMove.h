#pragma once
#include "SFML/Graphics.hpp"
class StrategyMove
{
public:

	virtual ~StrategyMove();

	void MoveS(sf::Time deltatime, sf::Sprite& _sprite, const float mov_speed);
};


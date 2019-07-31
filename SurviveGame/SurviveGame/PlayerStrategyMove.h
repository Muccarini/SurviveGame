#pragma once
#include "StrategyMove.h"

class PlayerStrategyMove :
	public StrategyMove
{
public:
	PlayerStrategyMove();
	virtual ~PlayerStrategyMove();

	
    void move(sf::Time deltatime, sf::Sprite& _sprite, const float mov_speed);
};


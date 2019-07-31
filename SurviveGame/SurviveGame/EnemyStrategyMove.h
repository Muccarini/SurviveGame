#pragma once
#include "StrategyMove.h"
class EnemyStrategyMove :
	public StrategyMove
{
public:
	virtual ~EnemyStrategyMove();

	void move(sf::Time deltatime, sf::Sprite& _sprite,const float mov_speed) override;
};


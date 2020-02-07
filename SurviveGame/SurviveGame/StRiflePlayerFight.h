#pragma once
#include "StrategyFight.h"

class StRiflePlayerFight :
	public StrategyFight
{
public:
	StRiflePlayerFight();
	virtual ~StRiflePlayerFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets,
		const std::shared_ptr<EntityData> entitydata);
	virtual const sf::Time getRatio();

protected:
	sf::Time ratio;
};


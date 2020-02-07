#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Entity.h"
class StrategyFight
{
public:
	explicit StrategyFight() = default;
	virtual ~StrategyFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets,
		const std::shared_ptr<EntityData> entitydata) = 0;
	virtual const sf::Time getRatio() = 0;
	int nrshot = 0;
};


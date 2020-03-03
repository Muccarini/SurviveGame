#pragma once
#include "StrategyFight.h"

class StGunPlayerFight :
	public StrategyFight
{
public:
	StGunPlayerFight();
	virtual ~StGunPlayerFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets,
		const std::shared_ptr<EntityData> entitydata);
};


 
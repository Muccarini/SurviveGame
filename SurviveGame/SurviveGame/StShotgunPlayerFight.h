#pragma once
#include "StrategyFight.h"
#include "PlayerT.h"
class StShotgunPlayerFight :
	public StrategyFight
{
public:
	StShotgunPlayerFight();
	virtual ~StShotgunPlayerFight() = default;

	void shot(std::vector<std::shared_ptr<Bullet>>& bullets, 
		const std::shared_ptr<EntityData> entitydata);
};


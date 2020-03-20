#pragma once
#include "StrategyFight.h"
#include "PlayerT.h"

class StShotgunPlayerFight :
	public StrategyFight
{
public:
	StShotgunPlayerFight();
	virtual ~StShotgunPlayerFight() = default;

	void shot(std::vector<std::shared_ptr<Bullet>>& bullets, BulletOwner::Owner owner,
		const sf::Vector2f owner_pos, const sf::Vector2f target_pos, const sf::Texture & texture)override;
};


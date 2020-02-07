#include "StShotgunPlayerFight.h"
#include <iostream>

StShotgunPlayerFight::StShotgunPlayerFight()
{
	this->ratio = sf::seconds(1.f / 2.f);
	nrshot = 4;//deve essere pari
}

void StShotgunPlayerFight::shot(std::vector<std::shared_ptr<Bullet>>& bullets, const std::shared_ptr<EntityData> entitydata)
{
	float dir = 180.f / (nrshot * 360.f);
	int count = 0;
	if (nrshot % 2 == 0)
	{
		count = 1;
		for (int i = 0; i < nrshot; i++)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Player, entitydata));
			bullets.emplace_back(bullet);
			if (i % 2 != 0)
				bullet->setDir(dir * count);
			else 
				bullet->setDir(dir * (-count));
			if (i % 2 != 0 && i != 0)
				count++;
		}
	}
}

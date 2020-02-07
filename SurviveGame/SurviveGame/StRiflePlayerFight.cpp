#include "StRiflePlayerFight.h"

StRiflePlayerFight::StRiflePlayerFight()
{
	this->ratio = sf::seconds(1.f / 16.66667f);
	nrshot = 1;
}

void StRiflePlayerFight::shot(std::vector<std::shared_ptr<Bullet>>& bullets, const std::shared_ptr<EntityData> entitydata)
{
	std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Player, entitydata));
	bullets.emplace_back(bullet);
	bullet->setDir();
}

const sf::Time StRiflePlayerFight::getRatio()
{
	return this->ratio;
}

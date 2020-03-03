#include "StGunPlayerFight.h"

StGunPlayerFight::StGunPlayerFight()
{
	this->ratio = sf::seconds(1.f / 4.f);
	nrshot = 5;//deve essere pari
}

void StGunPlayerFight::shot(std::vector<std::shared_ptr<Bullet>>& bullets, const std::shared_ptr<EntityData> entitydata)
{
	for (int i = 0; i < nrshot; i++)
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Player, entitydata));
		float dx = entitydata->mouse_pos_view.x - entitydata->player->getPosition().x;
		float dy = entitydata->mouse_pos_view.y - entitydata->player->getPosition().y;
		float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
		sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
		bullet->setDir(normVect);
		bullets.emplace_back(bullet);
	}
}

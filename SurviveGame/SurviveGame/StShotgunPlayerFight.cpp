#include "StShotgunPlayerFight.h"

StShotgunPlayerFight::StShotgunPlayerFight()
{
	this->ratio = sf::seconds(1.f / 4.f);
	nrshot = 8;//deve essere pari
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

			float dx = entitydata->mouse_pos_view.x - entitydata->player->getPosition().x;
			float dy = entitydata->mouse_pos_view.y - entitydata->player->getPosition().y;

			float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
			sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
			sf::Vector2f dir_p;
			if (i % 2 != 0)
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * count));
				bullet->setDir(dir_p);
			}
			else
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * -count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * -count));
				bullet->setDir(dir_p);
			}
			if (i % 2 != 0 && i != 0)
				count++;
			bullets.emplace_back(bullet);
		}
	}
}

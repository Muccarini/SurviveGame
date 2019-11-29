#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}


int Character::getHp()
{
	return
		this->hp;
}

int Character::getMovSpeed()
{
	return
		this->mov_speed;
}

int Character::getAmmo()
{
	return
		this->ammo;
}

bool Character::isReloading()
{
	return
		this->reloading;
}

bool Character::isShooting()
{
	return
		this->shooting;
}

void Character::collisionWalls(std::vector<sf::FloatRect> walls)
{
	for (int i = 0; i != walls.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), walls[i], &out_mtv))
		{
			sprite.move(out_mtv);
		}
	}
}

void Character::collisionEnemies(std::vector<std::shared_ptr<Character>> enemies)
{
	for (int i = 0; i != enemies.size(); i++)
	{
		if (enemies[i]->getHitBox().getGlobalBounds() != this->hit_box.getGlobalBounds())
			if (sat_test(hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds(), &out_mtv))
			{
				sprite.move(out_mtv);
			}
	}
}

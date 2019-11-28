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

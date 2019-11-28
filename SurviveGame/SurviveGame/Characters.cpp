#include "Characters.h"



Characters::Characters()
{
}


Characters::~Characters()
{
}

int Characters::getHp()
{
	return
		this->hp;
}

int Characters::getMovSpeed()
{
	return
		this->mov_speed;
}

int Characters::getAmmo()
{
	return
		this->ammo;
}

bool Characters::isReloading()
{
	return
		this->reloading;
}

bool Characters::isShooting()
{
	return
		this->shooting;
}

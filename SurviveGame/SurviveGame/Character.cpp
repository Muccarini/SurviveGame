#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

void Character::renderHud(std::shared_ptr<sf::RenderWindow> target)
{
	hud.renderTextsCharacter(target);
}


void Character::boostHeal()
{
	if ((this->hp = this->hp + 30) > this->hp_max)
		this->hp = this->hp_max;
}

void Character::boostMovSpeed()
{
	this->mov_speed += 100;
}

int Character::getHp()
{
	return
		this->hp;
}

int Character::getHpMax()
{
	return
		this->hp_max;
}

int Character::getMovSpeed()
{
	return
		this->mov_speed;
}

int Character::getMovSpeedDef()
{
	return
		this->mov_speed_default;
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
	return shooting;
}




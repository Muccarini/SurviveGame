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

bool Character::isAllied()
{
	return this->allied;
}

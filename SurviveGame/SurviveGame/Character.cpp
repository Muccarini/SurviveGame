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

float Character::getMovSpeed()
{
	return
		this->mov_speed;
}

float Character::getMovSpeedDef()
{
	return
		this->mov_speed_default;
}

int Character::getAmmo()
{
	return
		this->ammo;
}

void Character::setRatioCd(sf::Time ratio)
{
	this->ratio_cd = ratio;
}

const sf::Time Character::getRatioCd()
{
	return this->ratio_cd;
}

CharacterType::Type Character::getType()
{
	return this->type;
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




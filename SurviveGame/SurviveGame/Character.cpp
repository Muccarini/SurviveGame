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


bool Character::isShooting(sf::Time deltaTime)
{
	ratio -= deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !reloading)
	{
		if (ratio < sf::seconds(0.f))
		{
			ratio = sf::seconds(1.f / 16.666);
			return true;
		}
	}
	return false;
}

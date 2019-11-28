#pragma once
#include "Entity.h"
#include "Hud.h"

class Character :
	public Entity
{
public:
	Character();
	virtual ~Character();

	int getHp();
	int getMovSpeed();
	int getAmmo();
	bool isReloading();
	bool isShooting();

protected:
	Hud gui;

	sf::Time reload_cd;
	sf::Time reload_clock;
	sf::Time ratio;

	sf::CircleShape range;

	int hp;
	int hp_max;

	int mov_speed;
	int mov_speed_max;

	int ammo;
	int max_ammo;

	bool reloading;
	bool shooting;
};


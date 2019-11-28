#pragma once
#include "Entity.h"
#include "Hud.h"

class Characters :
	public Entity
{
public:
	Characters();
	virtual ~Characters();

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

	int hp;
	int hp_max;

	int mov_speed;
	int mov_speed_max;

	int ammo;
	int max_ammo;

	bool reloading;
	bool shooting;
};


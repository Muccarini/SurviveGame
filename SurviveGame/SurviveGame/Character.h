#pragma once
#include "Entity.h"
#include "Hud.h"
#include "Bullet.h"
#include <math.h>


namespace CharacterType
{
	enum Type { Melee, Ranged, Boss, Player};
}

class Character :
	public Entity
{
public:
	Character();
	virtual ~Character();

	void renderHud(std::shared_ptr<sf::RenderWindow> target);
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target) = 0;

	virtual void takeDamage() = 0;
	void boostHeal();
	void boostMovSpeed();

	int getHp();
	int getHpMax();

	int getMovSpeed();
	int getMovSpeedDef();

	int getAmmo();

	bool isReloading();
	bool isShooting();

protected:
	Hud hud;
	CharacterType::Type type;

	sf::Time reload_cd;
	sf::Time reload_clock;

	sf::Time ratio_cd;
	sf::Time ratio_clock;

	float range;

	int hp;
	int hp_max;

	int ammo;
	int ammo_max;

	bool reloading;
	bool shooting;
};


#pragma once
#include "Entity.h"
#include "Hud.h"
#include "Bullet.h"
#include <math.h>

namespace PlayerType
{
	enum Type { Type1, Type2, Type3 };
}

namespace EnemyType
{
	enum Type { Melee, Ranged };
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
	bool isShooting(sf::Time deltaTime);

protected:
	Hud hud;

	sf::Time reload_cd;
	sf::Time reload_clock;

	sf::Time ratio_cd;
	sf::Time ratio_clock;

	sf::CircleShape range;

	int hp;
	int hp_max;

	int ammo;
	int ammo_max;

	bool reloading;
	bool shooting;
};


#pragma once
#include "Entity.h"
#include "Hud.h"

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

	int getHp();
	int getMovSpeed();
	int getAmmo();
	bool isReloading();
	bool isShooting(sf::Time deltaTime);

protected:

	Hud hud;

	sf::Time reload_cd;
	sf::Time reload_clock;
	sf::Time ratio;

	sf::CircleShape range;

	int hp;
	int hp_max;

	int ammo;
	int ammo_max;

	bool reloading;
	bool shooting;
};


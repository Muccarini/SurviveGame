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

	int getHp();
	int getMovSpeed();
	int getAmmo();
	bool isReloading();
	bool isShooting();

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionEnemies(std::vector<std::shared_ptr<Character>> enemies);

protected:

	Hud hud_character;

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


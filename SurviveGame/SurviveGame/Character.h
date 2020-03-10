#pragma once
#include "Entity.h"
#include "Hud.h"
#include <math.h>


namespace CharacterType
{
	enum Type { Shotgun, Rifle, Handgun, Player};
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

	float getMovSpeed();
	float getMovSpeedDef();

	int getAmmo();
	void setAmmo(int i);

	void setRatioCd(sf::Time ratio);
	const sf::Time getRatioCd();

	CharacterType::Type getType();

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

	bool reloading = false;
	bool shoot;
};


#pragma once
#include "Character.h"
#include "StrategyFight.h"

class PlayerT : public Character
{
public:
	explicit PlayerT(const std::shared_ptr<EntityData> entitydata, Textures::ID id, StrategyFight* stf);

	PlayerT();
	virtual ~PlayerT();

	virtual void update();
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove();
	void updateBullets();
	void updateRotate();
	void updateReload();
	void updateDash(sf::Vector2f dir);
	void updateMovSpeed();
	void updateHud();
	void updateCollision();
	void updateDataPlayer();

	void updateShooting();
	void setStrategyFight(StrategyFight* stf);

	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;

	virtual void takeDamage();

	sf::Texture texture_movspeed;
	sf::Texture texture_bullet;
	Textures::ID id;

	float dash_speed;
	float dash_cd;
	float dash_clock;

	float ms_cd;
	float ms_clock;

	bool is_dashing;
protected:
	StrategyFight* stf;
	void setType();

	int kills;
	int kills_boss;

};


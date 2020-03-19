#pragma once
#include "Character.h"
#include "boost.h"
#include "StrategyFight.h"

class StrategyFight;

class PlayerT : public Character
{
public:
	explicit PlayerT(Textures::ID id, std::shared_ptr<StrategyFight> stf);

	PlayerT();
	virtual ~PlayerT();

	void updateMove(sf::Time deltaTime);
	void updateRotate(sf::Vector2f target);
	bool updateReload(sf::Time deltaTime);
	//void updateDash(sf::Time deltaTime, TileMap tile_map);
	void updateMovSpeed(sf::Time deltaTime);
	void updateHud();

	void boost(BoostType::Type b_type);

	bool shooting(sf::Time deltaTime);
	void setStrategyFight(std::shared_ptr<StrategyFight> stf);

	void initVar();
	void initSprite();
	void initHitBox();

	Textures::ID getId();
	std::shared_ptr<StrategyFight> getStf();

	void setTexturesSprite(const sf::Texture & texture);

	sf::Texture texture_movspeed;
	sf::Texture texture_bullet;

	sf::Vector2f mov_dir;

private:

	Textures::ID id;
	std::shared_ptr<StrategyFight> stf;
	void setType();

	int kills;
	int kills_boss;

	float dash_speed;
	float dash_cd;
	float dash_clock;

	float ms_cd;
	float ms_clock;

	bool is_dashing;

};

